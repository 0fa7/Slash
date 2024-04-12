// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

UCLASS()
class SLASH_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* BirdCapsule;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* BirdMesh;
	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* FloatingMovement;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* BirdSpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* BirdCamera;
	
	void MoveForward(const FInputActionInstance& Instance);
	void MoveRight(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);

	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveRightAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
