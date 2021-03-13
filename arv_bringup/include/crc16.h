#ifndef CRC16_H
#define CRC16_H

void CRC16CheckSum(uint8_t *pDataIn, int len, uint8_t *sum);
void CRC16CheckSum(uint8_t *pDataIn, int len, uint16_t *sum);

#endif // CRC16_H
