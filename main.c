#include "linked.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void pickQueue(Queue q[], int queueCount);
void processQueue(Queue q[], int queueCount);
void printAllQueue(Queue q[], int queueCount);
void exitApp(Queue q[], int queueCount);
void printMenu();
Queue *pickWhichQueue(Queue q[], int queueCount);
void clearTerminal();

int main() {
  bool isRunning = true;
  void (*tab[])(Queue q[], int queueCount) = {pickQueue, processQueue,
                                              printAllQueue, exitApp};

  int queueCount;
  printf("Banyak Antrian: ");
  scanf("%d", &queueCount);
  Queue q[queueCount];
  for (int i = 0; i < queueCount; i++) {
      createQueue(&q[i]);
  }
  while (isRunning) {
    int a;
    printMenu();
    scanf("%d", &a);
    tab[a - 1](q, queueCount);
  }

  return 0;
}

Queue *pickWhichQueue(Queue q[], int queueCount) {
  printf("Pilih queue yang mana? (1-%d): ", queueCount);
  int a;
  scanf("%d", &a);
  return &q[a - 1];
}

void pickQueue(Queue q[], int queueCount) {
  clearTerminal();
  for (int i = 0; i < queueCount; i++) {
    printf("Jumlah antrian ke-%d: %d\n", i + 1, NbElmt(q[i]));
  }
  address newNode;
  Queue *selected = pickWhichQueue(q, queueCount);
  // printf("%d, %d", selected, q[0]);
  infotype now = 0;
  if (!isEmpty(*selected)) {
      Queue temp = *selected;
      while (!isEmpty(temp->next)) {
          temp = temp->next;
      }
      now = temp->info;
  }
  Create_Node(&newNode);
  Isi_Node(&newNode, now+1);
  Enqueue(selected, newNode);
}
void processQueue(Queue q[], int queueCount) {
  clearTerminal();
  Queue *selected = pickWhichQueue(q, queueCount);
  bool dequed = false;
  infotype X, next;
  if (!isEmpty(*selected)) {
    Dequeue(selected, &X);
    dequed = true;
  }
  bool isRunning = true;
  while (isRunning) {
    if (dequed) {

      printf("Diproses: %d\n", X);
      if (!isEmpty(*selected)) {

        printf("Up next: %d\n", (*selected)->info);
      }
    } else {
      printf("Tidak ada antrian..\n");
    }
    char a;
    printf("Input q untuk keluar... \n");
    getchar();
    scanf("%c", &a);
    if (a == 'q') {
      isRunning = false;
    }
  }
}
void printAllQueue(Queue q[], int queueCount) {
  bool isRunning = true;
  while (isRunning) {
    clearTerminal();
    for (int i = 0; i < queueCount; i++) {
      Tampil_List(q[i]);
    }
    char a;
    printf("Input q untuk keluar... \n");
    getchar();
    scanf("%c", &a);
    if (a == 'q') {
      isRunning = false;
    }
  }
}

void clearTerminal() { system("clear"); }
void exitApp(Queue q[], int queueCount) {
  clearTerminal();
  for (int i = 0; i < queueCount; i++) {
    DeAlokasi(&q[i]);
  }
  exit(0);
}
void printMenu() {
  clearTerminal();
  printf("[APLIKASI TELLER BANK]\n");
  printf("1. Ambil Nomer Antrian\n");
  printf("2. Proses Antrian\n");
  printf("3. Cetak Antrian\n");
  printf("4. Exit Aplikasi\n");
}
