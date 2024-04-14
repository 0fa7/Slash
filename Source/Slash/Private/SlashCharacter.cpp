// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"

// Sets default values
ASlashCharacter::ASlashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair -> SetupAttachment(GetMesh()); 
	Hair->AttachmentName = "head";
	
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = "head";
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlashCharacter::MoveForward(const FInputActionInstance& Instance)
{
	const auto Value = Instance.GetValue().Get<float>();

	if(Value == 0.f)
	{
		return;
	}
	
	const auto ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
	const auto Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ASlashCharacter::MoveRight(const FInputActionInstance& Instance)
{	const auto Value = Instance.GetValue().Get<float>();

	if(Value == 0.f)
	{
		return;
	}
	
	const auto ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
	const auto Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ASlashCharacter::Look(const FInputActionInstance& Instance)
{
	AddControllerYawInput(Instance.GetValue().Get<FVector2D>().X);
	AddControllerPitchInput(Instance.GetValue().Get<FVector2D>().Y * -1.f);
}

// Called every frame
void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		Input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ASlashCharacter::MoveForward);	
	}

	if(MoveRightAction)
	{
		Input->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ASlashCharacter::MoveRight);
	}

	if(LookAction)
	{
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
	}

	if(JumpAction)
	{
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	}
}

