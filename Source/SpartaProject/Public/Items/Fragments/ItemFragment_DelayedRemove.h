#pragma once

#include "CoreMinimal.h"
#include "Fragments/ItemFragment_DelayedAction.h"
#include "ItemFragment_DelayedRemove.generated.h"

UCLASS()
class UItemFragment_DelayedRemove : public UItemFragment_DelayedAction
{
	GENERATED_BODY()

public:
	virtual void DelayedAction() override;
};
