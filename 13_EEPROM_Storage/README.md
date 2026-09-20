# 13. EEPROM Storage

## 🎯 학습 목표
*   아두이노 내부의 **EEPROM** 비휘발성 메모리를 사용하여, 전원이 꺼져도 설정값이나 중요한 데이터를 보관하는 법을 배웁니다.

## 💻 주요 함수
*   `EEPROM.write(address, value)`: 특정 주소에 데이터 쓰기
*   `EEPROM.read(address)`: 특정 주소의 데이터 읽기
*   `EEPROM.update(address, value)`: 값이 바뀔 때만 쓰기(수명 연장)
