// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NinjaGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class INIFINTERUNNER_API UNinjaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="health")
    int32 Health=3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
        TSubclassOf<class AMapTile>MapBlueprint;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
        int32 ScorePoints = 0;
    
protected:
    

public:
    UFUNCTION()
        void Score(int32 Value);

    UFUNCTION()
        void ChangeHealth(int32 value);

  
    
};
