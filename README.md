# Introduction to 

## 1. OAS algorithm

https://link.springer.com/content/pdf/10.1007/3-540-44418-1_14.pdf

## 2. 사용방법

NewOas 알고리즘을 사용하기 위해선, 기존의 Network의 파라미터를 저장해야합니다.
파라미터를 저장하는 형식은
~~~
input node 개수
disjunction node 개수(0을 넣으시면 됩니다)
output node 개수
conjunction node 개수(총 hidden layer node 개수)
~~~
개수들을 넣으신 후 차례대로 입력을 받게 됩니다.
input node의 정보
node#"node_number" "input" "input_node이름"
"다음 히든레이어 갯수" "노드 번호들"
형태로 node마다 파라미터 정보들을 넣게 됩니다.

example
~~~
node#0  input  x1
         4    5 6 7 8 
node#1  input  x2
         4    5 6 7 8 
node#2  input  x3
         4    5 6 7 8 
node#3  input  x4
         4    5 6 7 8 
~~~
그 뒤에는 output node의 정보, conjunction node의 정보가 오게됩니다.
node#"node_number" "input" "input_node이름" "bias"
"이전 layer 노드 개수" ("노드번호" "노드_파라미터" 개수만큼 반복)
이런 형태로 들어오게 됩니다.

example
~~~
node#4  output  y1 1.0400397
         3    9 -4.8122873 10 8.281093 11 -6.243534 
node#5  conjunction  h1 -2.0125153
         4    0 -0.09807512 1 -0.14931294 2 4.1039305 3 4.222266 
node#6  conjunction  h2 -0.440242
         4    0 -0.6702155 1 0.3070696 2 1.6526893 3 0.5896394 
~~~

최종적으로 이런 형태의 파라미터 file을 입력해야 합니다.
~~~
tf_BALLON1.nnf
4
0
1
7
node#0  input  x1
         4    5 6 7 8 
node#1  input  x2
         4    5 6 7 8 
node#2  input  x3
         4    5 6 7 8 
node#3  input  x4
         4    5 6 7 8 
node#4  output  y1 1.0400397
         3    9 -4.8122873 10 8.281093 11 -6.243534 
node#5  conjunction  h1 -2.0125153
         4    0 -0.09807512 1 -0.14931294 2 4.1039305 3 4.222266 
node#6  conjunction  h2 -0.440242
         4    0 -0.6702155 1 0.3070696 2 1.6526893 3 0.5896394 
node#7  conjunction  h3 -1.1152353
         4    0 -0.22509515 1 -0.2778535 2 2.6594408 3 2.5711136 
node#8  conjunction  h4 1.0356147
         4    0 -0.24504262 1 -0.09121176 2 -1.4856552 3 -1.7023321 
node#9  conjunction  h5 1.2975317
         4    5 -2.7874298 6 -0.8869413 7 -1.8993037 8 2.3087397 
node#10  conjunction  h6 -2.5420783
         4    5 4.728864 6 0.62498397 7 2.0092852 8 -1.6719774 
node#11  conjunction  h7 1.9784497
         4    5 -3.9341516 6 -0.1585242 7 -2.2391655 8 1.7479622 
~~~

2번쨰 input layer 모양을 file로 넣어주어야합니다.
실행속도를 줄이기 위해, discrete data인 경우 discrete data의 input 범위를 넣어주시면 됩니다.
예를들어 총 input 노드 개수가 12, 이산화된 부분이 0~3 7~11 일경우 이런형태가 됩니다.
~~~
5
4 1 1 1 5
~~~
만약 이산화를 쓰지 않을 경우
~~~
model_tf_BALLON1.nnf
0
~~~
0만 넣어주시면 됩니다. file이름은 항상 "model_" + "파라미터 파일이름"으로 정해집니다.

그 이후 NewOAS.exe 파일을 실행하면 됩니다.

~~~ 
NewOAS.exe "파라미터 파일 이름"
~~~
NewOAS 알고리즘을 적용하여 각 노드마다 Rule Exatraction을 실행합니다.
결과는 공통적으로 "RULE_EXTRACTION"으로 들어가게 됩니다. 
그 이후 최종적으로 
~~~
NewRewrite.exe "최종적인 출력파일 이름" "파라미터 파일이름" "option"
~~~
입력받게 됩니다. option은 output의 positive Rule만 출력시 1, negative Rule만 출력시 0, 둘다 출력시 2를 출력하게 됩니다.
