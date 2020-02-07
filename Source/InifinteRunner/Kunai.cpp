// Fill out your copyright notice in the Description page of Project Settings.


#include "Kunai.h"
#include "Components/StaticMeshComponent.h"
#include"Components/BoxComponent.h"
#include"PaperSpriteComponent.h"
#include "GameFramework/PlayerController.h"
#include "Ninjaharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include"Sound/SoundCue.h"
#include"NinjaGameInstance.h"



// Sets default values
AKunai::AKunai()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Mesh->SetupAttachment(RootComponent);
	//speed that will be used to move the actor
	MovingRate = 1200.f;
	//the rotation of the actor on the X and Z axis will be locked 
	Mesh->BodyInstance.bLockXRotation = true;
	Mesh->BodyInstance.bLockZRotation = true;

	OnActorBeginOverlap.AddDynamic(this, &AKunai::Collision);
}

// Called when the game starts or when spawned
void AKunai::BeginPlay()
{
	Super::BeginPlay();
	//after 5 seconds the actor will be destroyed
	SetLifeSpan(5.f);
}

// Called every frame
void AKunai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Only the mesh will rotate where in order to give the actor a spinning animation
	FRotator KunaiRotation = Mesh->GetComponentRotation();
	KunaiRotation.Pitch += DeltaTime * 25.f;
	Mesh->AddLocalRotation(FRotator(-20.f, 0.f, 0.f), false, 0, ETeleportType::None);

	// the actor will move in the direction of his Local X axis and not in the world X axis
	FVector location = GetActorLocation();
	location.X +=  DeltaTime;
	AddActorLocalOffset(FVector(20.f,0.f,0.f), true);



}

void AKunai::Collision(AActor* actor, AActor* otheractor)
{
	UNinjaGameInstance* GameInstance = Cast<UNinjaGameInstance>(GetGameInstance());

	if (otheractor->ActorHasTag("Enemy"))
	{
		UGameplayStatics::PlaySound2D(this, ExplosionSound);
		otheractor->Destroy();
		//every time this actor colides with an enemy, the EnemysKilled value will be incremented
		EnemysKilled++;
		//if this actor destroys 3 or more enemys the score will be increased by 30 for each enemy destroyed
		if (EnemysKilled>=3)
		{
			GameInstance->Score(30);
		}
		//otherwise only 10 points will be added to the score
		else
		{
			GameInstance->Score(10);

		}
	}
}



