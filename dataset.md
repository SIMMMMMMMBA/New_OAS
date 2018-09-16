

Dataset

1.xor
2.input_x>=2
3.input_x = 2
4.left>right
5.left>=right
6.ballon1
7.ballon2
8.ballon3
9.ballon4
10.iris



## 1. Rewrite 알고리즘 갱신

 기존 Rewrite시 mutual model 참조 안했었어서 엄청 느렸었음, 다만 매 노드마다 mutual  중 모순이 생기는 걸 삭제 해줌.

## 2. 속도비교

히든 Layer 4 2일 때
accuracy: 0.9222222

1) before

![1536538510071](C:\Users\Beom\AppData\Local\Temp\1536538510071.png)

2) after

![1536538533458](C:\Users\Beom\AppData\Local\Temp\1536538533458.png)

히든 Layer 6 4일 때
accuracy: 0.9444444

1) before![1536539935256](C:\Users\Beom\AppData\Local\Temp\1536539935256.png)

2)