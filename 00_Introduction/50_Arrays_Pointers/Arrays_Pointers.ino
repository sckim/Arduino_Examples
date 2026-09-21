/*
 * Arrays_Pointers
 * ----------------
 * 배열과 포인터의 기초.
 *
 * 왜 중요한가: 나중에 레지스터를 직접 다루거나(포인터로 메모리 주소 접근),
 * 여러 값을 한꺼번에 다루는 예제(02_Segment_Display의 세그먼트 패턴 배열 등)를
 * 보면 전부 배열/포인터로 되어 있다. 여기서 기초를 다져두면 그 코드들이
 * 훨씬 자연스럽게 읽힌다.
 *
 * 선행 학습: 40_Functions
 * 다음 단계: 60_String (문자열은 사실 char의 배열이다)
 */

void printArray(int arr[], int len) {   // 배열은 함수에 넘기면 사실 "시작 주소"만 전달된다
  for (int i = 0; i < len; i++) {
    Serial.print(arr[i]);
    Serial.print(' ');
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== 배열(Array): 같은 종류의 값을 여러 개 저장 ==="));
  int ledPins[5] = {2, 3, 4, 5, 6};
  Serial.print(F("ledPins 배열: "));
  printArray(ledPins, 5);
  Serial.print(F("ledPins[0] = ")); Serial.println(ledPins[0]);
  Serial.print(F("ledPins[4] = ")); Serial.println(ledPins[4]);

  Serial.println();
  Serial.println(F("=== 포인터(Pointer): 변수의 '주소'를 저장하는 변수 ==="));
  int x = 42;
  int* p = &x;      // &x = x의 메모리 주소. p는 그 주소를 저장한다.
  Serial.print(F("x 의 값        : ")); Serial.println(x);
  Serial.print(F("&x (x의 주소)  : ")); Serial.println((unsigned long)&x);
  Serial.print(F("p (저장된 주소): ")); Serial.println((unsigned long)p);
  Serial.print(F("*p (주소가 가리키는 값): ")); Serial.println(*p);  // *p = p가 가리키는 곳의 값

  *p = 100;         // 포인터를 통해 x의 값을 "간접적으로" 바꿔본다
  Serial.print(F("*p = 100; 실행 후 x의 값 -> ")); Serial.println(x);

  Serial.println();
  Serial.println(F("=== 배열 이름은 사실 '첫 번째 요소의 포인터'다 ==="));
  int* q = ledPins;          // 배열 이름 그대로가 &ledPins[0] 과 같다
  Serial.print(F("*q       = ")); Serial.println(*q);       // ledPins[0]
  Serial.print(F("*(q + 1) = ")); Serial.println(*(q + 1)); // ledPins[1] 과 동일! 포인터 연산
  Serial.print(F("q[2]     = ")); Serial.println(q[2]);      // 포인터도 [] 로 접근 가능
}

void loop() {
}
