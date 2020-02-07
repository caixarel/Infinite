// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkingOnPlatform.h"
#include"Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
AWalkingOnPlatform::AWalkingOnPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Box;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);

	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	OnActorBeginOverlap.AddDynamic(this, &AWalkingOnPlatform::Collision);
	OnActorEndOverlap.AddDynamic(this, &AWalkingOnPlatform::EndCollision);
	Sprite->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AWalkingOnPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWalkingOnPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWalkingOnPlatform::Collision(AActor* self, AActor* otherActor)
{
	//on the start of the collision the collision response will be set to Overlap
	//this way the Ninja Character can jump through the platfrom 
	Sprite->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AWalkingOnPlatform::EndCollision(AActor* self, AActor* otherActor)
{
	//when the overlap ends this actor collission response will change to Block 
	//now the Ninja Character can walk on this platform
	Sprite->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

}

