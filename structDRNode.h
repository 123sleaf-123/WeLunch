#ifndef STRUCTDRNODE_H
#define STRUCTDRNODE_H

typedef struct DRNode{
        char Id_DR[20];
        char DRName[400];
        int DRType;

        char DRLog[20];
        char DRLat[20];
        double Disatance;

        char DRImagePath[400];
        int DRSales;
        float DRgrade;
        char DRAvgDeliveryTime[400];

        char Id_Owner[20];
        bool compensate;
        bool redPacket;
        bool rebate;
        bool freeShipping;
        struct DRNode *next;
}*DRList;

#endif // STRUCTDRNODE_H
