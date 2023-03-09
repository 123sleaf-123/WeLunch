#include "restaurant.h"

Restaurant::Restaurant()
{

}



QString Restaurant::getDRId(){
    return this->Id_DR;
}

QString Restaurant::getDRName(){
    return this->DRName;
}

QString Restaurant::getDRType(){
    return this->DateCreated;
}

QString Restaurant::getDRCity(){
    return this->DRCity;
}

QString Restaurant::getDRLog(){
    return this->DRLog;
}

QString Restaurant::getDRLat(){
    return this->DRLat;
}

QString Restaurant::getTimeOpen(){
    return this->TimeClose;
}

int Restaurant::getCapacity(){
    return this->Capacity;
}

QString Restaurant::getDRIntroduction(){
    return this->DRIntroduction;
}

QString Restaurant::getDRImagePath(){
    return this->DRImagePath;
}

int Restaurant::getBaseFare(){
    return BaseFare;
}

int Restaurant::getDeliveryFee(){
    return DeliveryFee;
}

int Restaurant::getDRSales(){
    return DRSales;
}

float Restaurant::getDRRating(){
    return DRRating;
}

int Restaurant::getDRTotalTakeOutOrderNum(){
    return DRTotalTakeOutOrderNum;
}

int Restaurant::getDRTotalTakeOutOrderTime(){
    return DRTotalTakeOutOrderTime;
}

int Restaurant::getDRAvgDeliveryTime(){
    return DRAvgDeliveryTime;
}

void Restaurant::setDRId(QString in_Id_DR){
    Id_DR = in_Id_DR;
}

void Restaurant::setDRName(QString in_DRName){
    DRName = in_DRName;
}

void Restaurant::setDRType(QString in_DRType){
    DRType = in_DRType;
}

void Restaurant::setDateCreated(QString in_DateCreated){
    DateCreated = in_DateCreated;
}

void Restaurant::setDRCity(QString in_DRCity){
    DRCity = in_DRCity;
}

void Restaurant::setDRLog(QString in_DRLog){
    DRLog = in_DRLog;
}

void Restaurant::setDRLat(QString in_DRLat){
    DRLat = in_DRLat;
}

void Restaurant::setTimeOpen(QString in_TimeOpen){
    TimeOpen = in_TimeOpen;
}

void Restaurant::setTimeClose(QString in_TimeClose){
    TimeClose = in_TimeClose;
}

void Restaurant::setCapacity(int in_Capacity){
    Capacity = in_Capacity;
}

void Restaurant::setDRIntroduction(QString in_DRIntroduction){
    DRIntroduction = in_DRIntroduction;
}

void Restaurant::setDRImagePath(QString in_DRImagePath){
    DRImagePath = in_DRImagePath;
}

void Restaurant::setBaseFare(int in_BaseFare){
    BaseFare = in_BaseFare;
}

void Restaurant::setDeliveryFee(int in_DeliveryFee){
    DeliveryFee = in_DeliveryFee;
}

void Restaurant::setDRSales(int in_DRSales){
    DRSales = in_DRSales;
}

void Restaurant::setDRRating(float in_DRRating){
    DRRating = in_DRRating;
}

void Restaurant::setDRAvgDeliveryTime(int in_DRAvgDeliveryTime){
    DRAvgDeliveryTime = in_DRAvgDeliveryTime;
}

