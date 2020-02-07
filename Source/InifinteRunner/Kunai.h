// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kunai.generated.h"

UCLASS()
class INIFINTERUNNER_API AKunai : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKunai();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UPaperSpriteComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "rotation")
	float MovingRate ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " sound")
		class USoundCue* ExplosionSound;

	int32 EnemysKilled=0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Collision(AActor* actor, AActor* otheractor);
	
};
