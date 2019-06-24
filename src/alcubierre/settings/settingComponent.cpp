#pragma once

#include <string>
using namespace std;

class settingComponent
{
private:

	string _Identifier;
	string _Description;

	bool _varBool;
	int _varInt;
	long _varLong;
	string _varString;
	float _varFloat;
	double _varDouble;

public:

	//sets
	void SetIdentifier(string Identifier_Property) { _Identifier = Identifier_Property; }
	void SetDescription(string Description_Property) { _Description = Description_Property; }

	void SetBool(bool Boolean_Value){_varBool = Boolean_Value;}
	void SetInt(int Interger_Value) { _varInt = Interger_Value; }
	void SetLong(long Long_Value) { _varLong = Long_Value; }
	void SetString(string String_Value) { _varString = String_Value; }
	void SetFloat(float Floating_Point_Value) { _varFloat = Floating_Point_Value; }
	void SetDouble(double Double_Value) { _varDouble = Double_Value; }

	//gets
	string GetIdentifier() { return _Identifier; }
	string GetDescription() { return _Description; }

	bool GetBool() { return _varBool; }
	int GetInt() { return _varInt; }
	long GetLong() { return _varLong; }
	string GetString() { return _varString; }
	float GetFloat() { return _varFloat; }
	double GetDouble() { return _varDouble; }

	settingComponent(string Identifier)
	{
		this->SetIdentifier(Identifier);
	}

	settingComponent(string Idenfifier, string Description)
	{
		this->SetIdentifier(Idenfifier);
		this->SetDescription(Description);
	}

};