import time

def solution(numlist, n):
    # 버블 sort를 이용하여 단순하게 구현
    list_len = len(numlist)

    for i in range(list_len): # 마지막 원소는 정렬 필요 X
        for j in range(0, list_len - i - 1):
            # 인접한 두 원소 num1, num2를 가져옴
            num1 = numlist[j]
            num2 = numlist[j+1]
            
            # n과의 거리를 계산하는데 절댓값 기준으로 정렬
            dist1 = abs(n - num1)
            dist2 = abs(n - num2)
            
            # 정렬 조건 확인:
            # 1. num2가 num1보다 n에 더 가깝거나 (dist2 < dist1)
            # 2. 거리가 같으면서 num2가 num1보다 클 때 (dist1 == dist2 and num2 > num1)
            # 두 원소의 위치를 바꿈
            if dist2 < dist1 or (dist1 == dist2 and num2 > num1):
                temp = numlist[j]
                numlist[j] = numlist[j+1]
                numlist[j+1] = temp
    
    # 정렬된 리스트를 반환
    return numlist

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