// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InifinteRunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INIFINTERUNNER_API AInifinteRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AInifinteRunnerGameModeBase();
public:
	virtual void Tick(float DeltaTime);
	virtual void BeginPlay() override;



	float TimeForMaxDifficulty = 300;
	float MinValue = 0.5;
	float MaxValue = 3.0;
	float TimePassed = 0;
	float TimeToEnemy = 3;
	float Difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<class AEnemy> Enemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<class ADamageBlock> Block;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<class ADamageBlock> Spikes;
};
