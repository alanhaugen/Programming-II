#include "Bullet.h"
#include <Kismet/GameplayStatics.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraComponent.h>
#include "Enemy.h"

ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	RootComponent = BulletMesh;

	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBoxOverlap);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (this->GetActorForwardVector() * DeltaTime * MovementSpeed));
}

void ABullet::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Something was hit. If fire bolts are selected and the it did not hit the player, make an explosion (radial damage)
	if (BulletType == EAmmoTypes::EAT_Fire && Cast<AHarker>(OtherActor) == nullptr)
	{
		TArray<AActor*> ignoredActors;
		float ExplosionRadius = 500.0f;
		TSubclassOf<UDamageType> DamageType;

		UGameplayStatics::ApplyRadialDamage(GetWorld(),
			BulletDamage,
			GetActorLocation(),
			ExplosionRadius,
			DamageType,
			ignoredActors,
			this,
			nullptr,
			false,
			ECollisionChannel::ECC_Visibility);

		if (OnHitEffect && GetWorld())
		{
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OnHitEffect, GetActorLocation());
		}

		Destroy();
	}
	// Only deal damage if bullet overlaps enemies (unless it is a fire bolt)
	else if (Cast<AEnemy>(OtherActor))
	{
		// Call take damage on enemy: https://www.unrealengine.com/en-US/blog/damage-in-ue4
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(BulletDamage, DamageEvent, nullptr, this);
		
		if (OnHitEffect && GetWorld())
		{
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OnHitEffect, GetActorLocation(), GetActorRotation());
		}

		Destroy();
	}
}
