#include <stdio.h>
#include <stdlib.h>
#include "perpustakaan_common.h"
#include "perpustakaan_sll.h"
#include "perpustakaan_dll.h"
#include "perpustakaan_array.h"

/* Batalkan aktivitas terakhir */
void batalkanAktivitasTerakhir(void* perpusSLL, void* perpusDLL, void* perpusArray, Stack* stackAktivitas) {
    if (IsEmpty(stackAktivitas)) {
        printf("Tidak ada aktivitas untuk dibatalkan\n");
        return;
    }
    
    // Pop aktivitas dari stack
    Aktivitas* aktivitas = (Aktivitas*)Pop(stackAktivitas);
    
    if (aktivitas->tipeImplementasi == 1) {  // SLL
        batalkanAktivitasSLL((PerpustakaanSLL*)perpusSLL, aktivitas);
    } else if (aktivitas->tipeImplementasi == 2) {  // DLL
        batalkanAktivitasDLL((PerpustakaanDLL*)perpusDLL, aktivitas);
    } else if (aktivitas->tipeImplementasi == 3) {  // Array
        batalkanAktivitasArray((PerpustakaanArray*)perpusArray, aktivitas);
    } else {
        printf("Tipe implementasi tidak dikenal\n");
    }
    
    free(aktivitas);
}