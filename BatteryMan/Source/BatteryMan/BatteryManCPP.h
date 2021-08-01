// Fill out your copyright notice in the Description page of Project Settings.
// 0. Note from PL: Follow the numbered comments, they are personally made notes to describe things within the game


#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//1. Include components from the libray. These include the Camera, Capsule, Static Mesh, Inputs, Movement, Controller, Spring Arm and User Widget
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Blueprint/UserWidget.h"

//Make sure to include classes above the generate.h include or it won't work
#include "BatteryManCPP.generated.h"

//Define the variables you are going to use -PL

UCLASS()
class BATTERYMAN_API ABatteryManCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//2. Below is the constructor, it allows you to make an object out of the class
	ABatteryManCPP();

	//3. Create the folders using UPROPERTY. VisibleAnywhere means you can see the details of the object in the editor. BPReadOnly means you can see it in Blueprints. The Category is a Camera. CameraBoom is a use for Spring Arm and Follow Camera will be used to follow the player.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
	//4. Next go to the .cpp file...

	//19. Create the movement functions
	void MoveForward(float Axis);
	void MoveRight(float Axis);

	//20. Create the boolean that will be used to determine if the player is dead
	bool bDead;

	//21. Go back to the cpp..
	//24. Right click the movement functions, refactor and create definitions for them or type them out in .cpp file. 


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
