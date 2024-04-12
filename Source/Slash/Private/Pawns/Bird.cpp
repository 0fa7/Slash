// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BirdCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BirdCapsule"));
	SetRootComponent(BirdCapsule);
	BirdCapsule->SetCapsuleRadius(10.f);
	BirdCapsule->SetCapsuleHalfHeight(20.f);
	
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());

	BirdSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BirdSpringArm"));
	BirdSpringArm->SetupAttachment(GetRootComponent());
	BirdSpringArm->TargetArmLength = 300.f;
	BirdSpringArm->bInheritPitch = true;
	BirdSpringArm->bInheritYaw = true;
	BirdSpringArm->bUsePawnControlRotation = true;
	
	BirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BirdCamera"));
	BirdCamera->SetupAttachment(BirdSpringArm);
	
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABird::MoveForward(const FInputActionInstance& Instance)
{
	AddMovementInput(GetActorForwardVector(), Instance.GetValue().Get<float>());
}

void ABird::MoveRight(const FInputActionInstance& Instance)
{
	AddMovementInput(GetActorRightVector(), Instance.GetValue().Get<float>());
}

void ABird::Look(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("ABird::Look()"));
	AddControllerYawInput(Instance.GetValue().Get<FVector2D>().X);
	AddControllerPitchInput(Instance.GetValue().Get<FVector2D>().Y);
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GEngine->GetGamePlayer(GetWorld(), 0)->PlayerController->GetLocalPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent FAILED"));
	}
	
	// You can bind to any of the trigger events here by changing the "ETriggerEvent" enum value
	if(MoveForwardAction)
	{
		Input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ABird::MoveForward);	
	}

	if(MoveRightAction)
	{
		Input->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ABird::MoveRight);
	}

	if(LookAction)
	{
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::Look);
	}
}

