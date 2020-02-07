// Fill out your copyright notice in the Description page of Project Settings.


#include "BallEnemy.h"
#include"Components/SphereComponent.h"
#include"PaperSpriteComponent.h"
#include"NinjaGameInstance.h"
#include "Kismet\GameplayStatics.h"
#include"Particles/ParticleSystemComponent.h"
#include"Ninjaharacter.h"
#include "Sound/SoundCue.h"
#include"Kismet/GameplayStatics.h"

// Sets default values
ABallEnemy::ABallEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//setup of the collision sphere
	Box = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Box;
	Box->SetSphereRadius(10.f);

	//setup of the sprite used for this actor
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &ABallEnemy::Collide);	
}

// Called when the game starts or when spawned
void ABallEnemy::BeginPlay()
{
	Super::BeginPlay();
	//after 7 seconds this actor will be destroyed
	SetLifeSpan(7.f);
}

// Called every frame
void ABallEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//this actor will always move in the X 
	FVector Location = GetActorLocation();
	Location.X -= DeltaTime * 200;
	SetActorLocation(Location);
}

void ABallEnemy::Collide(AActor* Self, AActor* OtherActor)
{
	ANinjaharacter* ninja = Cast<ANinjaharacter>(OtherActor);
	//if this actor collides with an actor with Tag ninja and this Ninja actor is no attacking
	//the health of the Ninja actor will be reduced by 1 
	if (OtherActor->ActorHasTag("Ninja") && ninja->bIsAttacking==false)
	{
		UNinjaGameInstance* GameInstance = Cast<UNinjaGameInstance>(GetGameInstance());
		GameInstance->ChangeHealth(-1);
		if (OverlapParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.f), true);
			UGameplayStatics::PlaySoundAtLocation(this, CueSound, GetActorLocation());

		}
		Destroy();
	}
}





