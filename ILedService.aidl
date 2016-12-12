package android.os;

/** {@hide} */
interface ILedService
{
	int ledCtrl(int whichLed, int ledStatus);
}
