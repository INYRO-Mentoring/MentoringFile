import time

def solution(numlist, n):
    # sorted() 함수의 key를 사용하여 정렬 기준을 한 번에 적용합니다.
    # 이 방법은 O(n log n)의 시간 복잡도를 가지므로 훨씬 효율적입니다.
    # 1. 1차 기준: abs(n - x) -> n과의 거리를 오름차순으로 정렬
    # 2. 2차 기준: -x -> 거리가 같을 경우, 원래 숫자를 내림차순으로 정렬
    #    (숫자에 음수를 취해 오름차순 정렬하면 원래 숫자는 내림차순 정렬됩니다.)
    answer = sorted(numlist, key=lambda x: (abs(n - x), -x))
    
    return answer

def main() :
    n = int(input("n을 입력하세요: "))
    numlist_str = input("numlist를 공백으로 구분하여 입력하세요 (예: 10000 20 36 ...): ")
    numlist = list(map(int, numlist_str.split()))

    
    start_time = time.time()
    result = solution(numlist, n)
    end_time = time.time()

    duration_ms = (end_time - start_time) * 1000 ## ms 변환

    print("결과:", result)
    print(f"실행 시간: {duration_ms:.4f} ms")

if __name__ == "__main__" :
    main()

## 구현은 쉬움.
## 단 O(n^2) 으로 시간 복잡도가 증가함. 효율적이지 X
## 공간 복잡도 O(n) numlist의 배열만 존재.