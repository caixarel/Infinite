// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyNinjaCharacter.generated.h"

UENUM(BlueprintType)
enum class AnimationState :uint8 {
	AN_Running UMETA(DisplayName = "Running"),
	AN_Attack UMETA(DisplayName = "Attack"),
	AN_Dead UMETA(DisplayName = "Dead"),
	AN_Glide UMETA(DisplayName = "Glide"),
	AN_Jump UMETA(DisplayName = "Jump"),
	AN_JumpAttack UMETA(DisplayName = "JumpAttack"),
	AN_JumpThrow UMETA(DisplayName = "JumpThrow"),
	AN_Throw UMETA(DisplayName = "Throw")
};

UCLASS()
class INIFINTERUNNER_API AMyNinjaCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyNinjaCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		class UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		FVector BoxSize=(FVector(50.f,10.f,50.f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbookComponent* AnimationRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		class UPaperFlipbook* AnimationJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float RunningSpeed = 5;

	bool bIsOnGround;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void Jump();
	UFUNCTION()
		void NotJumping();
	UFUNCTION()
		void Attack();
	UFUNCTION()
		void NotAttacking();
	UFUNCTION()
		void Throw();
	UFUNCTION()
		void HitGround(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
