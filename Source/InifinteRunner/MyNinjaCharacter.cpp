// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNinjaCharacter.h"
#include"PaperFlipbook.h"
#include"PaperFlipbookComponent.h"
#include"Components/BoxComponent.h"
#include"Components/InputComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"UObject/ConstructorHelpers.h"
#include "PaperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"



// Sets default values
AMyNinjaCharacter::AMyNinjaCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Box;
	Box->InitBoxExtent(BoxSize);

	AnimationRunning = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Animation"));
	AnimationRunning->SetupAttachment(RootComponent);
	/*AnimationJumping = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Animationflip"));
	AnimationJumping->SetupAttachment(RootComponent);*/

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength=600.f;
	SpringArm->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	 ConstructorHelpers::FObjectFinder<UPaperFlipbook>Running(TEXT("PaperFlipbook'/Game/2dSprites/running/Run.Run'"));
	if (Running.Succeeded())
	{
		AnimationRunning->SetFlipbook(Running.Object);
	}
	OnActorHit.AddDynamic(this, &AMyNinjaCharacter::HitGround);
	bIsOnGround = false;
}

// Called when the game starts or when spawned
void AMyNinjaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyNinjaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	Location.X += RunningSpeed;
	SetActorLocation(Location);
}

// Called to bind functionality to input
void AMyNinjaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMyNinjaCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMyNinjaCharacter::NotJumping);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AMyNinjaCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &AMyNinjaCharacter::NotAttacking);

	PlayerInputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &AMyNinjaCharacter::Throw);
}

void AMyNinjaCharacter::Jump()
{
	
		AnimationRunning->SetFlipbook(AnimationJumping);
		bIsOnGround = false;
	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), bisGrounded);


}

void AMyNinjaCharacter::NotJumping()
{
	
}

void AMyNinjaCharacter::Attack()
{
	/*APlayerController* PlayerController = Cast<APlayerController>(GetController());
	float LocationX=0;
	float LocationY=0;
	PlayerController->GetMousePosition(LocationX, LocationY);*/
	UE_LOG(LogTemp, Warning, TEXT(" location "));
}

void AMyNinjaCharacter::NotAttacking()
{
	UE_LOG(LogTemp, Warning, TEXT(" location "));

}

void AMyNinjaCharacter::Throw()
{
}

void AMyNinjaCharacter::HitGround(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	bIsOnGround = true;
}

