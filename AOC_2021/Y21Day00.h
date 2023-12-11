#ifndef Y21DAY00_H
#define Y21DAY00_H

#include <QString>
#include <QVector>

class Y21Day00
{
public:
    Y21Day00();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;
};

#endif // Y21DAY00_H

#ifndef __ABSTRACT_HW_LAYER_HPP__
#define __ABSTRACT_HW_LAYER_HPP__
#include "TransactionConfigFacade.hpp"
#include "NativeOcppDef.hpp"


#include <zmq.h>
#include "zmq.hpp"
#include <string>

#include <cstdint>

/**
 * NATIVE_MeterDescription contains all necessary parameters for forwarding meter values,
 *  NB: trigger for sending might be triggered on Start, Stop, Status Notification,
 *  but also this might be dumped out of local cache.
 */
typedef struct __meterValues {
            int connectorId;
            int transactionId; //needed for OCPP local cache
            time_t		timestamp;
            std::string valueMeter;
            int context;
            int format;
            int measurand;
            int phase;
            int location;
            int units;
} NATIVE_MeterDescription;


/**
 * NATIVE_connectorStatus binds all necessary information to uniquely identify connector state,
 * error and their description by specific code(might be standard or vendor specific)
 */
typedef struct __connectorStatus {
                int chargePointStatus_status;
                int chargePointErrorCode;
                std::string info;
                std::string vendorId;
                std::string vendorErrorCode;
                bool IsEverSet;
} NATIVE_connectorStatus;


//forward declaration
 struct __chargingSchedule;
 typedef __chargingSchedule TChargingSchedule;
 //forward declaration
 struct __chargingProfile;
 typedef __chargingProfile TChargingProfile;

/**
 *  Abstract Platform X contains callbacks for above layer and its hardware and platform dependencies
 *  from OCPP implementation and simplifies porting on multiple platforms.
 */
 class AbstractPlatformX
{
    public:

     /**
      * Native States of Charge point
      */
     enum {
        Native__ChargePointStatus__Available = 0,    //!< Native__ChargePointStatus__Available considered to be same as NATIVE___AvailabilityType__Operative
        Native__ChargePointStatus__Preparing = 1,    //!< Native__ChargePointStatus__Preparing
        Native__ChargePointStatus__Charging = 2,     //!< Native__ChargePointStatus__Charging
        Native__ChargePointStatus__SuspendedEV = 3,  //!< Native__ChargePointStatus__SuspendedEV
        Native__ChargePointStatus__SuspendedEVSE = 4,//!< Native__ChargePointStatus__SuspendedEVSE
        Native__ChargePointStatus__Finishing = 5,    //!< Native__ChargePointStatus__Finishing
        Native__ChargePointStatus__Reserved = 6,     //!< Native__ChargePointStatus__Reserved
        Native__ChargePointStatus__Faulted = 7,      //!< Native__ChargePointStatus__Faulted
        Native__ChargePointStatus__Unavailable = 8   //!< Native__ChargePointStatus__Unavailable considered to be same as NATIVE___AvailabilityType__Inoperative
    };

     enum {
        Native__AvailabilityStatus__Accepted = 0,   //!< Native__AvailabilityStatus__Accepted
        Native__AvailabilityStatus__Rejected = 1,    //!< Native__AvailabilityStatus__Rejected
        Native__AvailabilityStatus__Scheduled = 2    //!< Native__AvailabilityStatus__Scheduled
    };

     /**
      * Each function in this Platform Abstraction should report if it has been successful or not.
      */
    enum
    {
        Abstract_Failed = 1,//!< Abstract_Failed
        Abstract_OK = 0     //!< Abstract_OK
    };

    enum
    {
        Native__RegistrationStatus__FORMAT_ERROR = -2,
        Native__RegistrationStatus__CONNECTION_Error = -1,
        Native__RegistrationStatus__Accepted = 0,
        Native__RegistrationStatus__Pending = 1,
        Native__RegistrationStatus__Rejected = 2
    };

    /**
     * NATIVE__ReservationStatus  Reservation Status of ReseveNow request.
     */
    enum
    {
        Native__ReservationStatus__Accepted = 0,
        Native__ReservationStatus__Faulted = 1,
        Native__ReservationStatus__Occupied = 2,
        Native__ReservationStatus__Rejected = 3,
        Native__ReservationStatus__Unavailable = 4
    };

    /**
     *  RegistrationStatus show the RegistrationStatus of BootNotification
     *
     * @param status  - status of BootNotification
     *
     */
    virtual void RegistrationStatus(int status) = 0;
    /**
     *  Set/Get  connectors availability can be changed locally from HW layer
     *    (in case of error, or connector layout, when f.e. CSS usage forbids ChaDemo usage)
     *    but also from central system;
     *    Might be used in above Layer above or also within OCPP Layer, in order to prove
     *    if incoming state from central system is valid of current situation.
     *
     * @param connectorId - might be also for global CP id 0 or specific connector
     * @param status  - status of connector*new in case of setter, or current one in case of Getter
     *
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int GetConnectorStatus(int connectorId, NATIVE_connectorStatus& status) = 0; //ok
    /**
     *
     *  Set/Get  connectors availability can be changed locally from HW layer
     *    (in case of error, or connector layout, when f.e. CSS usage forbids ChaDemo usage)
     *    but also from central system;
     *    Might be used in above Layer above or also within OCPP Layer, in order to prove
     *    if incoming state from central system is valid of current situation.
     *
     * @param connectorId - might be also for global CP id 0 or specific connector
     * @param status  - status of connector*new in case of setter, or current one in case of Getter
     *
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     *
     */
    virtual int SetConnectorStatus(int connectorId, const NATIVE_connectorStatus& status) = 0;//not yet used

    /**
     * Full reset call of HW with reboot, triggered from central system or after firmware update
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int ResetType__Hard() = 0;
    /**
     * Software reset without full reboot.
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int ResetType__Soft() = 0;


    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //not used any more and substituted with GetConnectorStatus
    //virtual int GetAvailability(int connectorId, unsigned int availabilityType) = 0;//not yet
    //not used any more and substituted with SetConnectorStatus
    virtual int SetAvailability(int connectorId, unsigned int availabilityType, unsigned int &availabilityStatus) = 0;//yes


    /**
     * @return true in case diagnostic is allowed,
     * false in case it's not good time to do this or
     *  must not be done(f.e. because FS is read only, and results file cannot be created)
     */
    virtual bool IsDiagnosticsAllowed() 	  	= 0;
    /**
     * @return  true in case clear cache is allowed, false in
     *  case it's not good time to do this or must not be done(f.e. because FS is read only, and results file cannot be created or DB is locked)
     */
    virtual bool IsClearCacheAllowed() 	  		= 0;
    /**
     * @return  true in case firmware update is allowed, false in
     *  case it's not good time to do this or must not be done(f.e. because FS is read only)
     */
    virtual bool IsUpdateFirmwareAllowed() 		= 0;
    /**
     * @return  true in case change configuration is allowed, false in
     *  case is not good time to do this or must not be done(f.e. because FS is read only)
     */
    virtual bool IsChangeConfigurationAllowed() = 0;
    /**
     * @return  true in case data transfer is allowed, false in
     *  case is not good time to do this or must not be done(f.e. because FS is read only)
     */
    virtual bool IsDataTransferAllowed() 		= 0;
    /**
     * @return  true in case remote start is allowed, false in
     *  case is not good time to do this or must not be done(f.e. because FS is read only)
     */
    virtual bool IsRemoteStartTransaction() 	= 0;

    /**
     * Trigger charging session from remote central system.
     * @param connectorId - connector on which charge triggered
     * @param idTag       - tag for which this remote charge is triggered
     * @param chargingSchedule  - charge schedule supposed for this charge session
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int RemoteStartTransaction(const int connectorId, std::string idTag, TChargingProfile* chargingSchedule) = 0; //, unsigned int &remoteStartStopStatus) = 0; //ok
    /**
     * Stop for currently running charge session remotely,
     * NB> remote service stops this by transaction, OCPP hides this from PAL(platform abstraction layer)
     * @param connectorId
     *
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int RemoteStopTransaction(int& connectorId) = 0; ///int transactionId) = 0;

    /**
     * Reserves connector from central system,
     * NB> connector might be 0 when whole CP could be reserved.
     * @param connectorId - connector for reservation
     * @param expiryDate  - expired data for reservation*(f.e. for GUI presentation)
     * @param idTag  - tag for which this connector is reserved*(f.e. for GUI presentation)
     * @param parentIdTag - parent Tag for which this connector*(f.e. for GUI presentation)
     * @param reservationId - reservation from central system*(f.e. for GUI presentation)
     * @param reservationStatus - the status of reservation.
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int ReserveNow(int connectorId, time_t expiryDate, std::string idTag, std::string *parentIdTag, int reservationId, unsigned int& reservationStatus) = 0;
    /**
     *
     * @param connectorId - connector for reservation cancel
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int CancelReservation(int connectorId) = 0 ;//ok

    /**
     * Central system might request the charge point to set the system time, in order to keep correct behaviour.
     * There are two way it might happen - as answer on BootNotification or Heart beat ..
     * @param newTime
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int BootNotificationSetTime(time_t newTime) = 0;
    /**
     * Central system might request the charge point to set the system time, in order to keep correct behaviour.
     * There are two way it might happen - as answer on BootNotification or Heart beat ..
     * @param newTime - new time
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int HeartbeatSetTime(time_t newTime) = 0;

    /**
     *  Functions should fill the meterValue field with necessary derivatives,
     *  function which call it should initialize:
     *	int connectorId < for which meter value is need, NB> could be 0 for whole CP energy
     *	int context < context of call is it on start, stop etc..
     * @param description  NATIVE_MeterDescription contains all necessary parameters for forwarding meter values,
     *  NB: trigger for sending might be triggered on Start, Stop, Status Notification,
     *  but also this might be dumped out of local cache.
     *
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */

    virtual int GetMeterValues(NATIVE_MeterDescription& description) = 0; //ok

    /**
     * Remote system might request composite schedule for appropriate connector and time slot,
     * this cannot be calculated within OCPP layer so far it depends on top many parameters(temperature, connector performance).
     *
     * @param connectorId - requested connector
     * @param duration - duration of charge profile
     * @param chargingRateUnit - rate unit
     * @param getCompositeScheduleStatus - status
     * @param connectorIdResponse - response
     * @param scheduleStart - start of charge schedule
     * @param chargingSchedule - requested charge schedule
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */

    virtual int GetCompositeSchedule(int connectorId, int duration, unsigned int* chargingRateUnit,
            unsigned int* getCompositeScheduleStatus, int* connectorIdResponse, time_t* scheduleStart, TChargingSchedule* chargingSchedule) = 0;
    /**
     * HW function in order to unlock connector,
     * NB above layer has to care about correct stop of charging and stop transactions and electric safe functionality.
     *
     * @param connectorId - requested connector for unlock
     * @param unlockStatus NATIVE__UnlockStatus__UnlockFailed = 1, NATIVE__UnlockStatus__NotSupported = 2 - should return
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    enum NATIVE__UnlockStatus__Unlocked
    {
        NATIVE__UnlockStatus__Unlocked = 0,
        NATIVE__UnlockStatus__UnlockFailed = 1,
        NATIVE__UnlockStatus__NotSupported = 2
    };
    virtual int OnUnlockConnector(int connectorId, unsigned  int &unlockStatus) = 0; //ok
    /**
     * Information call for above layer in order to inform about updated DB.
     *  Result currently is ignored, but might be important in case some FS changes are needed for this,.
     *  f.e sync.
     *
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int SentLocalList() 		 = 0; //ok
    /**
     * Information for above layer that some profile has been deleted within Profile Manager.
     * @param id - unique profile Id
     * @param connectorId - connector for which profile was deleted, NB might be 0 in this case supposed for the whole CP
     * @param chargingProfilePurpose - propose of this deleted profile
     * @param stackLevel - unique stack level of this profile
     * @return
     */
    virtual int ClearedChargingProfile(int *id, int *connectorId, unsigned int *chargingProfilePurpose, int *stackLevel) = 0; //ok
    /**
     * Information about updated charging profile in Profile Manager
     *
     * @param connectorId - connector for which profile has been updated,
     * 					NB: might be 0 in this case supposed for the whole CP
     *
     * @param csChargingProfile - changed charging profile
     *
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int SetChargingProfile(int connectorId, TChargingProfile* csChargingProfile) = 0;

    /**
     *
     * @param connectorId - stop transaction request for stop
     * @param stopTransaction - shall immediately stop
     * @param MaxEnergyOnInvalidIdWh - max energy provided for free
     * @return Abstract_Failed = 1, Abstract_OK  = 0
     */
    virtual int OnStopTransactionOnInvalidId(int connectorId, bool stopTransaction, int MaxEnergyOnInvalidIdWh) = 0;

    /**
     * Get the meter value of start transaction, which started from ISO15118.
     * @param connectorId - at which connector a transaction is started.
     */
    virtual int GetStartMeterValue(int connectorId) = 0;

    /**
     * Get the meter value of stop transaction, which stopped from ISO15118.
     * @param connectorId - at which connector a transaction is stopped.
     */
    virtual int GetStopMeterValue(int connectorId) = 0;
};


 class AbstractPlatformX;
 /**
  *
  */
 struct OCPP_ENGINE_CONFIGURATION
 {
     std::string 	link;
     int 			port;
     AbstractPlatformX* pAbstractPlatformX;
 } ;
 /**
  * Main interface for client code in order to communicate with
  *	OCPP backend and here all operations Initiated by Charge Point  declared.
  *	This interface has only hidden implementation
  *	and this implementation can only be created&initialized by GetNativeOcppEngine & InitializeEngine function.
  */
 class NativeOcppEngine
 {
     public:
     /**
      *  All functions like Authorize, StartTransaction returns 0 in case of authorization success or start transaction,
      *   in any other case return something else (f.e. error code)
      */
     enum NativeOcppEngine__Result {
         ///error codes..
         NativeOcppEngine_Failed = -1, //!< NativeOcppEngine_Failed
         NativeOcppEngine_Success = 0  //!< NativeOcppEngine_Success
     };

     /**
      * Authorize  has to be done before the owner of an electric vehicle can start or stop charging,
      * the Charge Point has to authorize the operation.
      * The Charge Point must only supply energy after authorization.
      * When stopping a Transaction, the Charge Point must only send an Authorize.req when
      * the identifier used for stopping the transaction is different from the identifier that started the transaction.
      *
      * @param tag  - RFID Tag  for authorization
      * @return NativeOcppEngine_Failed = -1, NativeOcppEngine_Success  = 0
      */
     virtual int Authorize(const std::string& tag) = 0;
     /**
      *
      * The client code should trigger send a StartTransaction.req PDU to
      * The the Central System to inform about a transaction that has been started.
      * The If this transaction ends a reservation (see Reserve Now operation),
      * then the StartTransaction.req MUST contain the reservationId.
      *
      * @param connectorId  - connector on which transaction is starting
      * @param tag  - RFID Tag  for transaction
      * @param meterX10  - meterValues on start
      * @param reservationId  - reservation for this authorisation
      *  @return NativeOcppEngine_Failed = -1, NativeOcppEngine_Success  = 0
      */
     virtual int StartTransaction(const int connectorId, const std::string& tag, const int& meterX10, const int reservationId = 0) = 0;
     /**
      *  If transaction is stopped,
      *  the Charge Point must send a StopTransaction.req PDU,
      *  notifying to the Central System that the transaction has stopped.
      *
      * @param connectorId  - connector on which transaction is stops
      * @param tag  - RFID Tag  for transaction
      * @param meterStop  - meter value on stop
      * @return NativeOcppEngine_Failed = -1, NativeOcppEngine_Success  = 0
      */
     virtual int StopTransaction(const int connectorId, const std::string& tag, int meterStop) = 0;

     /**
      *
      * CP sends a notification to the Central System to inform the Central System
      * about a status change or an error within the Charge Point.
      *  The enums above contains information.
      * @param connectorId  - connector on which transaction is stops
      * @param ChargePointStatus_status  - new status NativeOcppEngine__ChargePointStatus
      * @param ChargePointErrorCode  - error code*check NativeOcppEngine__ChargePointErrorCode
      * @param Info - Additional free format information related to the error.
      * @param VendorId - This identifies the vendor-specific implementation.
      * @param VendorErrorCode  - error vendor specific code
      * @return NativeOcppEngine_Failed = -1, NativeOcppEngine_Success  = 0
      *
      */
     virtual int StatusNotification(const int connectorId,
                                    const int ChargePointStatus_status,
                                    const int ChargePointErrorCode,
                                    const std::string Info = "",
                                    const std::string VendorId = "",
                                    const std::string VendorErrorCode = "") = 0;

     /**
      * InitMeterValue - Initialisation on NATIVE_MeterDescription structure, some values
      * are optional, but so far we allocate them on stack (! not on heat !), we have to know if they are used or empy.
      *
      *
      * @param meterDescription - struct for initialisation
      *
      * @return void
      */
     static void InitMeterValue(NATIVE_MeterDescription& meterDescription)
     {
         meterDescription.connectorId = 0;
         meterDescription.transactionId = 0; //needed for OCPP local cache
         meterDescription.timestamp  = 0;
         meterDescription.valueMeter = std::string("");
         meterDescription.context 	= NativeOcppDef::NATIVE__ReadingContext__Interruption__Empty;
         meterDescription.format 	= NativeOcppDef::NATIVE__ValueFormat__Empty;
         meterDescription.measurand 	= NativeOcppDef::NATIVE__Measurand__Current__Empty;
         meterDescription.phase 		= NativeOcppDef::NATIVE__Phase__Empty;
         meterDescription.location 	= NativeOcppDef::NATIVE__Location_Empty;
         meterDescription.units		= NativeOcppDef::NATIVE__UnitOfMeasure_Empty;
     }
     /**
      * MeterValues - send sampled energy meter or other sensor/transducer
      * hardware to provide extra information about its meter values to backend.
      *
      * @param connectorId - connector Id
      * @param timestamp  - timestamp meter value
      * @param valueMeter - meter value
      * @param context  - type of detail value: start, end or sample.
      * @param format  - raw or signed data
      * @param measurand - type of measurement
      * @param phase -  indicates how the measured value is to be interpreted.
      * @param location -  Location of measurement.
      * @param units - Unit of the value. Default = “Wh” if
      *
      * @return NativeOcppEngine_Failed = -1, NativeOcppEngine_Success  = 0
      */
     virtual int MeterValues(const int connectorId,
                 time_t timestamp,
                 std::string valueMeter,//energy meter state
                 int context,
                 int format,
                 int measurand,
                 int phase,
                 int location,
                 int units) = 0;
     /**
      * Initialization function, should be call before GetNativeOcppEngine
      *
      * @param link - link of remote backend
      * @param port - outgoing port
      * @param pAbstractPlatformX platform callbacks interface
      */


     virtual bool NetworkingProblemPresent() = 0;

     static void					InitializeEngine(std::string link, int port, AbstractPlatformX* pAbstractPlatformX = 0);
     static NativeOcppEngine*    GetNativeOcppEngine();

     virtual ~NativeOcppEngine() {}
     protected:
     NativeOcppEngine() {}
     private:
     static OCPP_ENGINE_CONFIGURATION m_configurationEngine;

 };

 enum {
         Native__ChargePointStatus__Available = 0,    //!< Native__ChargePointStatus__Available considered to be same as NATIVE___AvailabilityType__Operative
         Native__ChargePointStatus__Preparing = 1,    //!< Native__ChargePointStatus__Preparing
         Native__ChargePointStatus__Charging = 2,     //!< Native__ChargePointStatus__Charging
         Native__ChargePointStatus__SuspendedEV = 3,  //!< Native__ChargePointStatus__SuspendedEV
         Native__ChargePointStatus__SuspendedEVSE = 4,//!< Native__ChargePointStatus__SuspendedEVSE
         Native__ChargePointStatus__Finishing = 5,    //!< Native__ChargePointStatus__Finishing
         Native__ChargePointStatus__Reserved = 6,     //!< Native__ChargePointStatus__Reserved
         Native__ChargePointStatus__Faulted = 7,      //!< Native__ChargePointStatus__Faulted
         Native__ChargePointStatus__Unavailable = 8   //!< Native__ChargePointStatus__Unavailable considered to be same as NATIVE___AvailabilityType__Inoperative
     };

 enum NativeOcppEngine__ChargePointErrorCode {
         ChargePointErrorCode__ConnectorLockFailure = 0,
         ChargePointErrorCode__EVCommunicationError = 1,
         ChargePointErrorCode__GroundFailure = 2,
         ChargePointErrorCode__HighTemperature = 3,
         ChargePointErrorCode__InternalError = 4,
         ChargePointErrorCode__LocalListConflict = 5,
         ChargePointErrorCode__NoError = 6,
         ChargePointErrorCode__OtherError = 7,
         ChargePointErrorCode__OverCurrentFailure = 8,
         ChargePointErrorCode__OverVoltage = 9,
         ChargePointErrorCode__PowerMeterFailure = 10,
         ChargePointErrorCode__PowerSwitchFailure = 11,
         ChargePointErrorCode__ReaderFailure = 12,
         ChargePointErrorCode__ResetFailure = 13,
         ChargePointErrorCode__UnderVoltage = 14,
         ChargePointErrorCode__WeakSignal = 15
     };
