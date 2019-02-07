// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

UCLASS()
class EXPERIMENTALGAME2_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float AscentSpeedMod = 0.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetOtherPlayerEarComponent(USceneComponent* Ear);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USceneComponent* GetOtherPlayerEarComponent() { return OtherPlayerEarComponent; }

	class USceneComponent* OtherPlayerEarComponent;


protected:

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void Ascent(float Value);
	
	/**
 * Called via input to turn at a given rate.
 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void UpdateAudioListenerLocation();


};
