// Fill out your copyright notice in the Description page of Project Settings.

#include "Harker.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Kismet/KismetSystemLibrary.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Animation/AnimMontage.h>
#include "CheckPoint.h"

// Sets default values
AHarker::AHarker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate the character oddly with camera rotations
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	// Setup Camera Boom also known as Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true; // Let the Camera Boom (Spring Arm) move independantly from the rest

	// Setup Harker Character Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Make the Character face where it is moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.f, 0.0f);

	// Make the default items lantern and umbrella
	Lantern  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lantern"));
	Lantern->SetupAttachment(GetRootComponent());
	Umbrella = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Umbrella"));
	Umbrella->SetupAttachment(GetRootComponent());

	// Make the crossbow then hide it as it is not equipped by default
	Crossbow = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Crossbow"));
	Crossbow->SetupAttachment(GetRootComponent());
	Crossbow->ToggleVisibility();

	// Set first check point
	CurrentCheckPoint = nullptr;

	// Make an instance of this class the standard player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AHarker::BeginPlay()
{
	Super::BeginPlay();

	// Put lantern and umbrella in hands
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	Lantern->AttachToComponent(GetMesh(), TransformRules, "LeftHandSocket");
	Umbrella->AttachToComponent(GetMesh(), TransformRules, "RightHandSocket");
	Crossbow->AttachToComponent(GetMesh(), TransformRules, "RightHandGunSocket");

	// Enhanced Input Input Mapping Controller (IMC) Setup for The Castle Main Game Character Harker
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(HarkerContext, 0);
		}
	}
}

bool AHarker::MeleeAttack()
{
	if (isZoomingIn == false && ActionState == EActionState::EAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && AttackMontage)
		{
			AnimInstance->Montage_Play(AttackMontage);

			if (CharacterState == ECharacterState::ECS_Equipped)
			{
				Umbrella->ToggleVisibility();
				Crossbow->ToggleVisibility();
			}

			/*const int32 Selection = FMath::RandRange(0, 1);
			FName SelectionName;
			switch(Selection)
			{
			case 0:
				SelectionName = FName("Attack1");
				break;
			case 1:
				SelectionName = FName("Attack2");
				break;
			default:
			}

			AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);*/

			ActionState = EActionState::EAS_Attacking;
		}
		// Play animation montage
		// Damage nearby enemies

		return true;
	}

	return false;
}

bool AHarker::SpendAmmo()
{
	switch (SelectedAmmo)
	{
	case EAmmoTypes::EAT_Normal:
		if (AmmunitionNormal <= 0)
		{
			return false;
		}

		AmmunitionNormal--;
		break;
	case EAmmoTypes::EAT_Fire:
		if (AmmunitionFlame <= 0)
		{
			return false;
		}

		AmmunitionFlame--;
		break;
	case EAmmoTypes::EAT_Holy:
		if (AmmunitionHoly <= 0)
		{
			return false;
		}

		AmmunitionHoly--;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Ammo not supported"));
	}

	return true;
}

void AHarker::SpawnBullet()
{
	if (BulletToSpawn)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			FVector SpawnLocation = GetActorLocation();
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			World->SpawnActor<AActor>(BulletToSpawn, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void AHarker::MeleeAttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;

	if (CharacterState == ECharacterState::ECS_Equipped)
	{
		Umbrella->ToggleVisibility();
		Crossbow->ToggleVisibility();
	}
}

void AHarker::EquipWeapon()
{
	if (CharacterState != ECharacterState::ECS_Equipped)
	{
		// Show the crossbow
		Crossbow->ToggleVisibility();

		// Change the state of the character
		CharacterState = ECharacterState::ECS_Equipped;

		// Hide the default assets
		Lantern->ToggleVisibility();
		Umbrella->ToggleVisibility();
	}
}

// Called every frame
void AHarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.2f;         //Zoom in over half a second
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
	}

	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	// Blend our camera's FOV and our SpringArm's length based on ZoomFactor
	Camera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	SpringArm->SocketOffset = FVector(0.0f, 60.0f, 0.0f) * ZoomFactor;

	// Line trace

	/*FVector Start = Camera->GetComponentLocation();
	FVector Forward = Camera->GetForwardVector();
	FVector End = ((Forward * 1000.0f) + Start);
	FHitResult outHit;

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	
	TArray<AActor*> ignore;
	ignore.Add(GetOwner());
	ignore.Add(this);
	

	bool result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjectTypes, false, ignore, EDrawDebugTrace::ForOneFrame, OUT outHit, true);

	if (result) 
	{
		FString f = FString(outHit.GetActor()->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, f);
	}
	*/
	
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	// We set up a line trace from our current location to a point 1000cm ahead of us
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 5000.0f;

	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}

}

// Called to bind functionality to input
void AHarker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup action bindings (input mapping)
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHarker::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHarker::LookAround);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AHarker::Fire);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AHarker::Jump);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started , this, &AHarker::AimStart);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AHarker::AimEnd);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Completed, this, &AHarker::Interaction);
	}
}

void AHarker::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AHarker::LookAround(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AHarker::Fire()
{
	// If left mouse is clicked without aiming, fight via melee (swing umbrella)
	if (MeleeAttack())
	{
		return;
	}
	
	// Don't fire if no weapon is equipped or doing melee attack
	if (CharacterState == ECharacterState::ECS_Unequipped ||
		ActionState == EActionState::EAS_Attacking)
	{
		return;
	}

	// Try to fire crossbow based on selected ammunition, stop if out of ammo
	if (SpendAmmo() == false)
	{
		return;
	}

	// Spawn arrow/bullet from crossbow
	SpawnBullet();
}

void AHarker::AimStart(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Using Aim"));
	isZoomingIn = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
}

void AHarker::AimEnd(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Stopped Aim"));
	isZoomingIn = false;
}

void AHarker::Interaction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interact"));
	}

	if (CurrentCheckPoint)
	{
		CurrentCheckPoint->Load();
	}
}
