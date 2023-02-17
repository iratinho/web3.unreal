﻿#pragma once

#include "HTTP/Public/Interfaces/IHttpRequest.h"

class FWeb3BaseRequest
{
public:
	virtual ~FWeb3BaseRequest() = default;

	FString Url;
	int32 ChainID;
	FHttpRequestCompleteDelegate OnCompleteDelegate;

protected:
	void InitializeRequest();
	void FinalizeRequest() const;
	virtual void BuildRequest() = 0;
	
	typedef TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriterFactory;
	typedef TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriter;

	TSharedPtr<FJsonObject> RequestObject;
	TSharedPtr<FJsonObject> ChainObject;
	FString HttpContentString;
	FHttpRequestPtr Request;
};

class FWeb3RPCRequest : public FWeb3BaseRequest
{
public:
	FString Request;
	FString ParamsStrVar;
	FString ChainMetadataVar;
protected:
	virtual void BuildRequest() override;
};

class FWeb3PExternalRPCRequest : public FWeb3BaseRequest
{
public:
	FString RequestString;
protected:
	virtual void BuildRequest() override;
};

class FWeb3SendContractRequest : public FWeb3BaseRequest
{
public:
	FString ContractAddressVar;
	FString FunctionNameVar;
	FString ABIVar;
	FString ValueInWeiVar; //int64 is not big enough
	TArray<FString> ParamsVar;
	int32 GasLimitVar;
	
protected:
	virtual void BuildRequest() override;
};

// TODO For when implementing the call contract request 
class FWeb3CallContractRequest {};

template <typename RequestPolicy>
class FWeb3RequestBuilder : public RequestPolicy
{
public:
	void ExecuteRequest()
	{
		RequestPolicy::InitializeRequest();
		RequestPolicy::BuildRequest();
		RequestPolicy::FinalizeRequest();
	};
};
