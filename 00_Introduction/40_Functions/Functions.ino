/*
 * Functions
 * ----------
 * 함수의 기본 형태(매개변수, 반환값)와, 매크로(#define)와의 차이를 다룬다.
 *
 * 아두이노 스케치의 setup()/loop() 자체도 함수다. 지금까지 사용한
 * Serial.println() 도 남이 만들어둔 함수를 "호출"한 것일 뿐이다.
 *
 * 선행 학습: 30_Control_Flow
 * 다음 단계: 50_Arrays_Pointers
 */

// 매개변수 2개를 받아 그 합을 "반환(return)"하는 함수
int add(int a, int b) {
  return a + b;
}

// 반환값이 없는 함수는 void를 쓴다 (아무것도 돌려주지 않고 "실행"만 함)
void printLine(char ch, int count) {
  for (int i = 0; i < count; i++) {
    Serial.print(ch);
  }
  Serial.println();
}

// 함수 오버로딩(overloading, C++ 기능): 이름은 같지만 매개변수 종류가 다르면
// 서로 다른 함수로 취급된다. 아래는 int용, float용 두 가지 square()이다.
int square(int x) {
  return x * x;
}
float square(float x) {
  return x * x;
}

// 매크로: 함수처럼 보이지만 실제로는 "컴파일 전에 텍스트를 그대로 치환"하는 것뿐이다.
#define SQUARE_MACRO(x) (x * x)

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println(F("=== 함수 호출: add(3, 4) ==="));
  int result = add(3, 4);
  Serial.println(result);

  Serial.println();
  Serial.println(F("=== void 함수: printLine('-', 10) ==="));
  printLine('-', 10);

  Serial.println();
  Serial.println(F("=== 함수 오버로딩: square(int) vs square(float) ==="));
  Serial.println(square(5));      // int 버전 호출 -> 25
  Serial.println(square(2.5f));   // float 버전 호출 -> 6.25

  Serial.println();
  Serial.println(F("=== 매크로의 함정: SQUARE_MACRO(x) 는 텍스트 치환일 뿐! ==="));
  int n = 3;
  Serial.print(F("SQUARE_MACRO(n+1) 의 실제 결과: "));
  Serial.println(SQUARE_MACRO(n + 1));
  // 치환되면 (n+1 * n+1) = (3+1 * 3+1) 이 되는데, *가 +보다 먼저 계산되므로
  // 3 + (1*3) + 1 = 3 + 3 + 1 = 7 이 되어버린다!
  // 함수라면 (n+1)*(n+1) = 4*4 = 16 이 나올 것을 기대했겠지만 전혀 다른 값이다.
  Serial.println(F("괄호를 안 쳐서 곱셈 우선순위 때문에 3+(1*3)+1=7 이 됨. 기대한 16이 아님!"));
  Serial.print(F("반면 진짜 함수 square(n+1)의 결과: "));
  Serial.println(square(n + 1));  // 정상적으로 16
}

void loop() {
}
