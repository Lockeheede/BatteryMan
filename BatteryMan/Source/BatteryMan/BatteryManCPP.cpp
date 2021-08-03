// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryManCPP.h"

// Implement the variables to be used in the game

// Sets default values
ABatteryManCPP::ABatteryManCPP()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//4. First initalization will happen here. 
	//5. Create a Blueprint Folder and Class. Inherit from the BatteryManCPP Class. Open it up to see that it already has some of the components that were included in the .h file (Capsule, Mesh, Character Movement etc.). 
	//6. Inside the BP, add the Skeletal Mesh and position it. Resize the Capsule Component in CODE
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);


	//7. Make the camera, not character, to rotate.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//8. Make the character rotate towards the direction they are moving and create the speed (rate) of which they rotate while moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	//9. Also create the velocity of jumping, as well as the control you have while jumping
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	//10. Make the Spring Arm a Camera Boom with the name CameraBoom, which is the name you will see in the Blueprint Component. Then attach it to the RootComponent object
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	//11. How far away the spring arm is gonna be from the user. And if and how the spring arm rotates rotates (by the use of the controller)
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	//12. Create the camera with the component name FollowCamera. Then attach it to the Spring Arm/CameraBoom. Keep it from being rotated by the contoller, instead it sits on the CameraBoom
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//13. Ctrl+Shift+B to compile. This will literally build the things that are coded and MUST be done everytime something new is created so it can be a part of the BP, or whatever it is referencing.  
	//14. Now the BP Character will have a CameraBoom and Follow Camera attached to it
	//15. Next create a Game Mode CPP Class and Inherit from Game Mode. 
	//16. Then make a BP and select a BatteryMan_GameMode. Name it BatteryMan_GameMode_BP
	//17. In Project Settings, Maps and Modes, Make the Default Game mode the new BatteryMan_GameMode_BP; then make the Default Pawn the BatteryManCPP_BP

	//18. The Character cannot move yet, so we are going to declare and create functions. Go back to BatteryManCPP.h...

	//22. Set default of dead
	bDead = false;

	//23. Create functionally for movement, back in cpp...


}

//25. Functions created. MoveForward was refactored, MoveRight was typed out. Either one works Move the functions to the bottom of the code. 

// Called when the game starts or when spawned
void ABatteryManCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABatteryManCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABatteryManCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Before 26 Note: Input was created within the Project Settings Input

	//27.Binds the Turn from the Input for this class to the Pawn's Controller Yaw and Pitch Input
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//28. Bind Actions with pressing and releasing jump button.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//29. Bind MoveForward and MoveRight Actions
	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryManCPP::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryManCPP::MoveRight);

}

//26. Moved Functions to the bottom
void ABatteryManCPP::MoveForward(float Axis)
{
	//30. Calculate the move right direction of the character, as long as they are not dead
	if (!bDead)
	{
		//31. Create a Rotation FRotator variable and set it to equal the rotation of the controller? Then use that variable to set the YawRotation variable by its Y Axis
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ABatteryManCPP::MoveRight(float Axis)
{
	//30. Calculate the move right direction of the character, as long as they are not dead
	if (!bDead)
	{
		//31. Create a Rotation FRotator variable and set it to equal the rotation of the controller? Then use that variable to set the YawRotation variable by its Y Axis
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}


