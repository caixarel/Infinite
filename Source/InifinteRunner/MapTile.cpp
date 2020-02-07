// Fill out your copyright notice in the Description page of Project Settings.


#include "MapTile.h"
#include"Components/StaticMeshComponent.h"
#include"Components/BoxComponent.h"
#include"Kismet/GameplayStatics.h"
#include"NinjaGameInstance.h"
#include "Components/ArrowComponent.h"
#include"Enemy.h"
#include"DamageBlock.h"
#include"Ninjaharacter.h"


// Sets default values
AMapTile::AMapTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//mesh setup
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	//collider setup
	//when this collider is overlapped a new copie of this actor will be spawned creating a infinite platform
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Box->SetupAttachment(RootComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	Arrow->SetupAttachment(RootComponent);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AMapTile::MapGenerate);
}

// Called when the game starts or when spawned
void AMapTile::BeginPlay()
{
	Super::BeginPlay();
	//after 30 seconds this actor will be destroyed
	SetLifeSpan(30.f);
}

// Called every frame
void AMapTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMapTile::MapGenerate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//location where the next copie of this actor will be spawned
	FVector location = Arrow->GetComponentLocation();
	location.X += 500;
	//if this actor is overlapped by an actor with the tag "Ninja" a new version of the map will be spawned
	if (OtherComp->ComponentHasTag("Ninja"))
	{
		GetWorld()->SpawnActor<AMapTile>(MapBlueprint, location, FRotator::ZeroRotator);
	}
	
}

