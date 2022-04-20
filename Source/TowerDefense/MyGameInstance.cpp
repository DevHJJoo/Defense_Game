// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Manager/EffectMgr.h"

UMyGameInstance::UMyGameInstance()
{
}

UMyGameInstance::~UMyGameInstance()
{
	UEffectMgr::Destroy();
}