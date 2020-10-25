// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonMPTarget.h"
#include "ThirdPersonMPProjectile.h"
#include "ThirdPersonMPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonMPGameMode.h" 

// Sets default values
AThirdPersonMPTarget::AThirdPersonMPTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereComponent;

	//Definition for the Mesh that will serve as our visual representation.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	//Set the Static Mesh and its position/scale if we successfully found a mesh asset to use.
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation_Direct(FVector(0.0f, 0.0f, 0.0f));
		StaticMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
}

// Called when the game starts or when spawned
void AThirdPersonMPTarget::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AThirdPersonMPTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AThirdPersonMPTarget::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	FVector hitLocation = DamageCauser->GetActorLocation();
	FVector centerLocation = GetActorLocation();
	double targetDistance = (hitLocation - centerLocation).Size();
	double maxDistance = 250.0;
	double scoreRate = 10.0;
	double addAmount = (maxDistance - targetDistance) / scoreRate;
	//only update score on server
	if (GetLocalRole() == ROLE_Authority)
	{
		AThirdPersonMPGameMode* MyGameMode = (AThirdPersonMPGameMode*)UGameplayStatics::GetGameMode(this);
		if (MyGameMode->MatchStart && MyGameMode->MatchRemainTime >= 0) {
			AThirdPersonMPCharacter* shooter = (AThirdPersonMPCharacter*)(DamageCauser->GetOwner());
			shooter->AddScore(addAmount);
		}
	}
	return addAmount;
}


