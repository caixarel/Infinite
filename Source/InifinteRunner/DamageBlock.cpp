// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageBlock.h"
#include"Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include"NinjaGameInstance.h"
#include"Particles/ParticleSystemComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Sound/SoundCue.h"

// Sets default values
ADamageBlock::ADamageBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//collider setup
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Box;
	//sprite setup 
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &ADamageBlock::Collision);
}

// Called when the game starts or when spawned
void ADamageBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageBlock::Collision(AActor* self, AActor* otherActor)
{
	//this actor can only be destroyed when he collides with the actor with tag"Ninja" or with the Kunai actor 
	//if this actor collides with an actor with Tag ninja the health of the Ninja actor will be reduced by 1 
	if (otherActor->ActorHasTag("Ninja"))
	{
		UNinjaGameInstance* GameInstance = Cast<UNinjaGameInstance>(GetGameInstance());
		GameInstance->ChangeHealth(-1);
		if (OverlapParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.f), true);
		}
		if (OverlapSound)
		{
			UGameplayStatics::PlaySound2D(this, OverlapSound);

		}
		Destroy();
	}
	
}

