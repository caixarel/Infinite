// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Ninjaharacter.generated.h"

/**
 * 
 */
UCLASS()
class INIFINTERUNNER_API ANinjaharacter : public APaperCharacter
{
	GENERATED_BODY()
public:
    ANinjaharacter();
	//all the animations that will be played
	//this animations will be
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbookComponent* AnimationRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbook* AnimationJumping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbook* AnimationRun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbook* AnimationAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbook* AnimationJumpingAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbook* AnimationThrowing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbook* AnimationSlide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* CueSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* CueSoundFailSword;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* CueSoundThrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float RunningSpeed = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float jumpVel = 1000.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnThrow")
		TSubclassOf<class AKunai> ThrowKunai;

	FTimerHandle AttackTimer;
	FTimerHandle ThrowTimer;
	FTimerHandle SlideTimer;


	bool bIsOnGround;
	bool bIsAttacking;
	bool bIsThrowing;
	bool bisSliding;
	float LocationX = 0;
	float LocationY = 0;
	FVector Location;
	FVector Worldlocation;
	float Seconds=0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
		void Jumping();
	UFUNCTION()
		void NotJumping();
	UFUNCTION()
		void Attack();
	UFUNCTION()
		void NotAttacking();
	UFUNCTION()
		void Throw();
	UFUNCTION()
		void NotThrowing();
	UFUNCTION()
		void Sliding();
	UFUNCTION()
		void NotSliding();
	UFUNCTION()
		void Collision(AActor* SelfActor, AActor* OtherActor);
	
};
