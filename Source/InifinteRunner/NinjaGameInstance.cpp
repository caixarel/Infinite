// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaGameInstance.h"
#include "PaperTileSet.h"
#include"MapTile.h"
#include "Engine/World.h"
#include"Kismet/GameplayStatics.h"


void UNinjaGameInstance::Score(int32 Value)
{

	ScorePoints += Value;
}

void UNinjaGameInstance::ChangeHealth(int32 Value) {
	Health += Value;
	//when Health reaches 0 the game is over and the player goes to the GamepverMenu where he can choose to quit game or play again
	if (Health<=0)
	{
		
		UGameplayStatics::OpenLevel(this, "GameOverMenu", true);
		
	}	
}




