// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include"Components/BoxComponent.h"
#include"PaperSpriteComponent.h"
#include"TimerManager.h"
#include"BallEnemy.h"
#include"Engine/World.h"
#include"NinjaGameInstance.h"
#include"Particles/ParticleSystemComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Sound/SoundCue.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//collider setup
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Box;
	Box->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	//sprite setup
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	//when this actor his spawned it will immediately shoot a ball
	Shoot();
	OnActorBeginOverlap.AddDynamic(this, &AEnemy::Collision);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//the actor will move up and down
	FVector Location = GetActorLocation();
	Location.Z += DeltaTime * speed;
	SetActorLocation(Location);
	//this are the limites of the screen 
	//the code is preventing the actor of going outside the screen
	if (Location.Z>=40)
	{
		speed = -200.f;		
	}
	else if (Location.Z<=-590)
	{
		speed = 200.f;
	}

}

void AEnemy::Shoot()
{
	FVector ShootLocation = GetActorLocation();
	ShootLocation.X -= 100;
	GetWorldTimerManager().ClearTimer(ShootTimer);
	//Ball actor will be Spawned every 2 seconds
	GetWorld()->SpawnActor<ABallEnemy>(Ball, ShootLocation, FRotator::ZeroRotator);
	GetWorldTimerManager().SetTimer(ShootTimer, this, &AEnemy::Shoot, 2.f);

}

void AEnemy::Collision(AActor* Actor, AActor* OtherActor)
{
	//if this actor collides with an actor with Tag ninja the health of the Ninja actor will be reduced by 1 
	if (OtherActor->ActorHasTag("Ninja"))
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

