#include "SpartaCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

ASpartaCharacter::ASpartaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
	HPWidget->SetupAttachment(GetMesh());
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	MaxHealth = 100.0f;
	Health = MaxHealth;
}

float ASpartaCharacter::GetHealth() const
{
	return Health;
}

void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateHPWidget();
}

void ASpartaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput == nullptr)
	{
		return;
	}

	ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController());
	if (PlayerController == nullptr)
	{
		return;
	}

	if (PlayerController->MoveAction != nullptr)
	{
		EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Move);
	}
	if (PlayerController->JumpAction != nullptr)
	{
		EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartJump);
		EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &ASpartaCharacter::StopJump);
	}
	if (PlayerController->LookAction != nullptr)
	{
		EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Look);
	}
	if (PlayerController->SprintAction != nullptr)
	{
		EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartSprint);
		EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &ASpartaCharacter::StopSprint);
	}
}

float ASpartaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("TakeDamage"));

	if (Health <= 0.0f)
	{
		OnDeath();
	}
	UpdateHPWidget();
	return ActualDamage;
}

void ASpartaCharacter::AddHealth(float Amout)
{
	Health = FMath::Clamp(Health + Amout, 0.0f, MaxHealth);
	UpdateHPWidget();
	UE_LOG(LogTemp, Warning, TEXT("AddHealth"));
}

void ASpartaCharacter::OnDeath()
{
	ASpartaGameState* GameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (GameState)
	{
		GameState->OnGameOver();
	}
}

void ASpartaCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}
	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector, MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector RightVector = GetActorRightVector();
		AddMovementInput(RightVector, MoveInput.Y);
	}
}

void ASpartaCharacter::StartJump(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	if (Value.Get<bool>())
	{
		Jump();
	}
}

void ASpartaCharacter::StopJump(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	if (!Value.Get<bool>())
	{
		StopJumping();
	}
}

void ASpartaCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	FVector2D LookInput = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(LookInput.X))
	{
		AddControllerYawInput(LookInput.X);
	}

	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		AddControllerPitchInput(LookInput.Y);
	}
}

void ASpartaCharacter::StartSprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ASpartaCharacter::StopSprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void ASpartaCharacter::UpdateHPWidget()
{
	if (!IsValid(HPWidget))
	{
		return;
	}

	UUserWidget* WidgetInstance = HPWidget->GetUserWidgetObject();
	if (!IsValid(WidgetInstance))
	{
		return;
	}

	UProgressBar* HPBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("OverHeadHPBar")));
	if (!IsValid(HPBar))
	{
		return;
	}

	HPBar->SetPercent(Health / MaxHealth);

}
