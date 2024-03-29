/* Citation and Sources...
 * Final Project Milestone 5
 * Module: Vehicle
 * Filename: Vehicle.cpp
 * Version 1.0
 * Author	Tilak Kawa
 * Revision History
 * -----------------------------------------------------------
 *  Date        Reason
 *  2022/11/23  Preliminary release
 *  2022/11/23  Debugged DMA
 *  -----------------------------------------------------------
 *  I have done all the coding by myself and only copied the code 
 *  that my professor provided to complete my project milestones.
 *  -----------------------------------------------------------
 *  */

#define _CRT_SECURE_NO_WARNINGS
#include "Vehicle.h"
#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;
namespace sdds {
	Vehicle::Vehicle()
	{
		setEmpty();
	}
	Vehicle::Vehicle(const char* licensePlate, const char* makeModel) : ReadWritable()
	{
		if (licensePlate && makeModel && strlen(makeModel) >= 2 && strlen(licensePlate) > 0 && strlen(licensePlate) <= 8) {
			m_parkingSpotNumber = 0;
			setLicensePlate(licensePlate);
			setMakeModel(makeModel);
		}
		else {
			setEmpty();
		}

	}
	Vehicle::~Vehicle() {
		delete[] m_licensePlate;
		delete[] m_makeModel;
	}
	void Vehicle::setEmpty()
	{
		m_licensePlate = nullptr;
		m_makeModel = nullptr;
		m_parkingSpotNumber = -1;
	}
	bool Vehicle::isEmpty() const
	{
		if (m_parkingSpotNumber < 0) {
			return true;
		}
		return false;
	}
	const char* Vehicle::getLicensePlate() const
	{
		return m_licensePlate;
	}
	const char* Vehicle::getMakeModel() const
	{
		return m_makeModel;
	}
	void Vehicle::setMakeModel(const char* makeModel)
	{
		if (makeModel && strlen(makeModel) >= 2) {
			delete[] m_makeModel;
			m_makeModel = new char[strlen(makeModel) + 1];
			strcpy(m_makeModel, makeModel);
		}
		else {
			setEmpty();
		}

	}
	void Vehicle::setLicensePlate(const char* licensePlate)
	{
		delete[] m_licensePlate;
		m_licensePlate = new char[strlen(licensePlate) + 1];
		strcpy(m_licensePlate, licensePlate);
		for (int i = 0; m_licensePlate[i]; i++) {
			m_licensePlate[i] = toupper(m_licensePlate[i]);
		}
	}

	int Vehicle::getParkingSpot() const
	{
		return m_parkingSpotNumber;
	}
	void Vehicle::setParkingSpot(int parkingSpot)
	{
		if (parkingSpot >= 0) {
			m_parkingSpotNumber = parkingSpot;
		}
		else {
			setEmpty();
		}
	}
	bool Vehicle::operator==(const char* licensePlate) const
	{
		bool isEqual = true;
		if (m_licensePlate && licensePlate && (strlen(m_licensePlate) == strlen(licensePlate))) {
                        int length = strlen(m_licensePlate);
			for (int i = 0; i < length; i++) {
				if (toupper(m_licensePlate[i]) != toupper(licensePlate[i])) {
					isEqual = false;
					break;
				}
			}
		}
		else {
			isEqual = false;
		}
		return isEqual;
	}
	bool Vehicle::operator==(const Vehicle& secondVehicle) const
	{
		return secondVehicle == m_licensePlate;
	}
	std::istream& Vehicle::read(std::istream& istr)
	{
		int m_parkingSpotNumber = 0;

		char tempLic[10];
		char tempMModel[62];

		if (isCsv()) {
			istr >> m_parkingSpotNumber;
			istr.ignore();
			istr.get(tempLic, 9, ',');
			istr.ignore(1024, ',');
			istr.get(tempMModel, 61, ',');
			istr.ignore(1024, ',');
		}
		else {
			cout << "Enter License Plate Number: ";
			istr.get(tempLic, 10);
			istr.ignore(1024, '\n');
			while (strlen(tempLic) > 8) {
				cout << "Invalid License Plate, try again: ";
				istr.get(tempLic, 10);
				istr.ignore(1024, '\n');
			}
			cout << "Enter Make and Model: ";
			istr.get(tempMModel, 62);
			istr.ignore(1024, '\n');
			while (strlen(tempMModel) > 60 || strlen(tempMModel) < 2) {
				cout << "Invalid Make and model, try again: ";
				istr.get(tempMModel, 62);
				istr.ignore(1024, '\n');
			}
		}
		if (istr.fail()) {
			setEmpty();
			istr.clear();
		}
		else {
			setMakeModel(tempMModel);
			setParkingSpot(m_parkingSpotNumber);
			setLicensePlate(tempLic);
		}
		return istr;
	}
	std::ostream& Vehicle::write(std::ostream& ostr) const
	{
		if (isEmpty()) {
			ostr << "Invalid Vehicle Object" << endl;
		}
		else {
			writeType(ostr);
			if (isCsv()) {
				ostr << m_parkingSpotNumber << "," << m_licensePlate << "," << m_makeModel << ",";

			}
			else {
				ostr << "Parking Spot Number: ";
				if (m_parkingSpotNumber == 0) {
					ostr << "N/A";
				}
				else {
					ostr << m_parkingSpotNumber;
				}
				ostr << endl;

				ostr << "License Plate: " << m_licensePlate << endl;

				ostr << "Make and Model: " << m_makeModel << endl;
			}
		}
		return ostr;
	}
}
