// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninjaharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include"PaperFlipbook.h"
#include"PaperFlipbookComponent.h"
#include"Components/BoxComponent.h"
#include"Components/InputComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"UObject/ConstructorHelpers.h"
#include "PaperCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include"Kunai.h"
#include"TimerManager.h"
#include"Components/CapsuleComponent.h"
#include "Sound/SoundCue.h"
#include"Kismet/GameplayStatics.h"
#include "NinjaGameInstance.h"


ANinjaharacter::ANinjaharacter() {
	PrimaryActorTick.bCanEverTick = true;
	
	//Create a Flipbook component for the Main Animation(running animation)
	AnimationRunning = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Animation"));
	AnimationRunning->SetupAttachment(RootComponent);
	
	//spring arm for the camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	//camera will be set on orthographic projection mode
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);

	//The character can not change is rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	ConstructorHelpers::FObjectFinder<UPaperFlipbook>Running(TEXT("PaperFlipbook'/Game/2dSprites/running/Run.Run'"));
	if (Running.Succeeded())
	{
		AnimationRunning->SetFlipbook(Running.Object);
	}

	OnActorBeginOverlap.AddDynamic(this, &ANinjaharacter::Collision);
	
	bIsOnGround = false;
	//the jumping velocity was defined on the Header file
	GetCharacterMovement()->JumpZVelocity = jumpVel;
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	
}

void ANinjaharacter::BeginPlay()
{
	Super::BeginPlay();
	//setting the booleans to false in the begin of play
	bIsAttacking = false;
	bIsThrowing = false;
	//when GameOver Menu shows up and the player chooses to play again , the health and the ScorePoints 
	//should go back to their initial values when the Game restarts
	UNinjaGameInstance* GameInstance = Cast<UNinjaGameInstance>(GetGameInstance());
	GameInstance->ScorePoints=0;
	GameInstance->Health = 3;
}

void ANinjaharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//adding constant movement to the character
	Location = GetActorLocation();
	Location.X += RunningSpeed;
	SetActorLocation(Location);
	//the camera should not move up and down when the character jumps
	FVector CameraPos = Camera->GetComponentLocation();
	CameraPos.Z = -50.f;
	Camera->SetWorldLocation(CameraPos);

	//if the character is not attacking or throwing or sliding then he is just running
	if (GetCharacterMovement()->IsMovingOnGround() && bIsAttacking==false && bIsThrowing==false && bisSliding == false)
	{
		AnimationRunning->SetFlipbook(AnimationRun);
		UCapsuleComponent* capsule = Cast<UCapsuleComponent>(GetCapsuleComponent());
		//when the character is sliding the Capsule size is reduced and here i am setting it back to the initial value
		//because the character is no longer sliding
		capsule->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
		AnimationRunning->SetRelativeScale3D(FVector(0.375f, 1.f, 0.375f));
	}

	//every second the score will increment 1 point
	Seconds += DeltaTime;
	if (Seconds>=1)
	{
		UNinjaGameInstance* GameInstance = Cast<UNinjaGameInstance>(GetGameInstance());
		GameInstance->Score(1);
		Seconds = 0;
	}
}

void ANinjaharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ANinjaharacter::Jumping);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ANinjaharacter::NotJumping);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ANinjaharacter::Attack);
	PlayerInputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &ANinjaharacter::Throw);
	PlayerInputComponent->BindAction("Slide", EInputEvent::IE_Pressed, this, &ANinjaharacter::Sliding);
}

void ANinjaharacter::Jumping()
{
	//The Character class already has a Jumping function ,so i just call this function when the jump button is pressed
	Jump();
	//changes to the jumping animation
	AnimationRunning->SetFlipbook(AnimationJumping);
	bIsOnGround = false;
}

void ANinjaharacter::NotJumping()
{
	StopJumping();
	
}

void ANinjaharacter::Attack()
{
	//can only attack when all the booleans are false 
	if (bIsAttacking==false && bIsThrowing==false && bisSliding == false)
	{
		bIsAttacking = true;
		AnimationRunning->SetFlipbook(AnimationAttacking);
		UGameplayStatics::PlaySoundAtLocation(this, CueSoundFailSword, GetActorLocation());
		//delay until the character can attack again
		GetWorldTimerManager().SetTimer(AttackTimer, this, &ANinjaharacter::NotAttacking, 0.5f);
	}
	

}

void ANinjaharacter::NotAttacking()
{
	bIsAttacking = false;
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void ANinjaharacter::Throw()
{
	//can only throw when all the booleans are false 
	if (bIsAttacking == false && bIsThrowing == false && bisSliding == false)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		bIsThrowing = true;
		AnimationRunning->SetFlipbook(AnimationThrowing);

		FVector worldRotation;
		//Find the location of the mouse cursor relative to the world
		PlayerController->GetMousePosition(LocationX, LocationY);
		PlayerController->DeprojectMousePositionToWorld(Worldlocation, worldRotation);

		FVector PlayerLocation = GetActorLocation();
		PlayerLocation.X += 20;
		//used the FindLookAtRotation to calculate the angle between the character and the mouse cursor
		FRotator MouseAngle = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, Worldlocation);
		FRotator FindMouse = FRotator(MouseAngle.Pitch, 0.f, 0.f);
		//when the Kunai is spawn ,it will have a rotation matching the direction of the mouse cursor.the Kunai
		//will fly to the position where the cursor was when the kunai was thrown
		GetWorld()->SpawnActor<AKunai>(ThrowKunai, PlayerLocation, FindMouse);
		UGameplayStatics::PlaySoundAtLocation(this, CueSoundThrow, GetActorLocation());

		GetWorldTimerManager().SetTimer(AttackTimer, this, &ANinjaharacter::NotThrowing, 0.5f);

	}
	
}

void ANinjaharacter::NotThrowing()
{
	bIsThrowing = false;
	GetWorldTimerManager().ClearTimer(ThrowTimer);

}

void ANinjaharacter::Sliding()
{
	if (bIsAttacking == false && bIsThrowing == false && bisSliding==false)
	{
		bisSliding = true;
		AnimationRunning->SetFlipbook(AnimationSlide);
		//The capsule component is reduced to simulate a dashing effect 
		UCapsuleComponent* capsule =Cast<UCapsuleComponent>( GetCapsuleComponent());
		capsule->SetRelativeScale3D(FVector(1.f, 1.f, 0.5f));
		AnimationRunning->SetRelativeScale3D(FVector(0.375f, 1.f, 0.57f));
		GetWorldTimerManager().SetTimer(SlideTimer, this, &ANinjaharacter::NotSliding, 0.5f);
	}
}

void ANinjaharacter::NotSliding()
{
	bisSliding = false;
	GetWorldTimerManager().ClearTimer(SlideTimer);

}

void ANinjaharacter::Collision(AActor* SelfActor, AActor* OtherActor)
{
	//if the character overlaps something and is attacking will do the following:
	if (bIsAttacking==true)
	{
		//if the actor overlapped has a Enemy or Ball Tag then:
		if (OtherActor->ActorHasTag("Enemy")|| OtherActor->ActorHasTag("Ball"))
		{
			//a sound hurting the character will be played
			UGameplayStatics::PlaySoundAtLocation(this, CueSound, GetActorLocation());
			//the actor overlapped by the character will be destroyed
			OtherActor->Destroy();
			UNinjaGameInstance* GameInstance = Cast<UNinjaGameInstance>(GetGameInstance());
			//the score will be incremented 5 points
			GameInstance->Score(5);
		}
		
	}
}
