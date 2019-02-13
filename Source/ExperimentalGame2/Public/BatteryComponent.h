// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BatteryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBatteryDelegate, int32, BatteryWarningIndex);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENTALGAME2_API UBatteryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBatteryComponent();

	UPROPERTY(EditAnywhere, Category = "Setup")
	float BatteryDrainingAmount = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float BatteryDrainingPeriod = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ZeroBatteryMovementSpeed = 100;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupBatteryDrainingTimer();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetBatteryPercent() const { return CurrentPercent; }

	UFUNCTION(BlueprintCallable)
	void CostBatteryPercent(float DeltaPercent);

	UFUNCTION(BlueprintCallable)
	void RecoverBatteryPercent(float DeltaPercent);

	class UFloatingPawnMovement* GetMovementComponent() const;

	void StartZeroBatteryMode();

	void RecoverMovement();

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FBatteryDelegate OnBatteryDrained;

private:
	float InitialPercent = 100;
	UPROPERTY(VisibleAnywhere)
	float CurrentPercent = 100;

	float InitialMaxSpeed;

	FTimerHandle BatteryTimerHandle;

};
