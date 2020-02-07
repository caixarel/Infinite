// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapTile.generated.h"

UCLASS()
class INIFINTERUNNER_API AMapTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapTile();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
		class UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
	TSubclassOf< class AMapTile>MapBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
		class UArrowComponent* Arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
		TSubclassOf< class ADamageBlock>Block;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
		TSubclassOf< class AEnemy>Enemy;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void MapGenerate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
