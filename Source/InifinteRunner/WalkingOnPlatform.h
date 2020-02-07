// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WalkingOnPlatform.generated.h"

UCLASS()
class INIFINTERUNNER_API AWalkingOnPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWalkingOnPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "collisionBox")
		class UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
		class UPaperSpriteComponent* Sprite;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Collision(AActor* self, AActor* otherActor);
	UFUNCTION()
		void EndCollision(AActor* self, AActor* otherActor);
};
