// Fill out your copyright notice in the Description page of Project Settings.


#include "InifinteRunnerGameModeBase.h"
#include "Ninjaharacter.h"
#include"Kismet/GameplayStatics.h"
#include"Engine/World.h"
#include"Enemy.h"
#include"DamageBlock.h"


AInifinteRunnerGameModeBase::AInifinteRunnerGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}
void AInifinteRunnerGameModeBase::BeginPlay() {
	Super::BeginPlay();
}

void AInifinteRunnerGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ANinjaharacter* ninja = Cast<ANinjaharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FVector NinjaLocation = ninja->GetActorLocation();
	//Here i create a random X Axis position between 2 values to be used later as the spawn location of the enemys
	NinjaLocation.X += 1000;
	float RandomPositionX = FMath::FRandRange(NinjaLocation.X, (NinjaLocation.X + 1500));
	float RandomPositionX2 = FMath::FRandRange(NinjaLocation.X, (NinjaLocation.X + 1500));
	float RandomPositionX3 = FMath::FRandRange(NinjaLocation.X, (NinjaLocation.X + 1300));
	//same thing as above but for the Y Axis
	//there is no RandomPositionY3 because i want the Enemy "Spikes" to be always on the ground
	float RandomPositionY = FMath::FRandRange(-590.f, 0);
	float RandomPositionY2 = FMath::FRandRange(-590.f, -320);

	//Difficulty Setup
	// the difficulty will increase as the time psses
	TimePassed += DeltaTime;
	//the time that will take to spawn the enemys
	TimeToEnemy -= DeltaTime;
	//when TimeToEnemy is inferior to 0 ,Enemys will be spawned
	if (TimeToEnemy < 0)
	{
		//The difficulty percentage is calculated here
		//the difficulty percentage will reach 100% or 1 at 300Seconds and will increase no more
		Difficulty = FMath::Min(TimePassed / TimeForMaxDifficulty, 1.0f);
		//at maximun difficulty enemys will be spawned every 0.5seconds
		TimeToEnemy = MaxValue - (MaxValue - MinValue) * Difficulty;
		GetWorld()->SpawnActor<AEnemy>(Enemy, FVector(RandomPositionX, 0, RandomPositionY), FRotator::ZeroRotator);
		GetWorld()->SpawnActor<ADamageBlock>(Block, FVector((RandomPositionX2 +200), 0, RandomPositionY2), FRotator::ZeroRotator);
		GetWorld()->SpawnActor<ADamageBlock>(Spikes, FVector((RandomPositionX3 + 200), 0, -580), FRotator::ZeroRotator);

	}
}
