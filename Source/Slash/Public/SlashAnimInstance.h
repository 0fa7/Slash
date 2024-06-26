// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"

class UCharacterMovementComponent;
class ASlashCharacter;
/**
 * 
 */
UCLASS()
class SLASH_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	ASlashCharacter* SlashCharacter;
	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* SlashCharacterMovement;
	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;
	UPROPERTY(BlueprintReadOnly)
	bool IsFalling;
	
};
