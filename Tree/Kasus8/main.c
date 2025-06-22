#include <stdio.h>
#include <stdlib.h>
#include "nbtrees.h"

void display_tree_structure(Isi_Tree T, int idx, int level) {
    int i;
    
    /* Display current node */
    for (i = 0; i < level; i++) {
        printf("    ");
    }
    printf("|-- %c\n", T[idx].info);
    
    /* Display first son */
    if (T[idx].ps_fs != nil) {
        display_tree_structure(T, T[idx].ps_fs, level + 1);
    }
    
    /* Display next brother */
    if (T[idx].ps_nb != nil) {
        display_tree_structure(T, T[idx].ps_nb, level);
    }
}

void display_tree(Isi_Tree T) {
    if (IsEmpty(T)) {
        printf("Tree is empty!\n");
        return;
    }
    
    printf("\nTree Structure:\n");
    display_tree_structure(T, 1, 0);
    printf("\n");
}

void create_sample_tree(Isi_Tree T) {
    /* Clear tree */
    int i;
    for (i = 0; i <= jml_maks; i++) {
        T[i].info = ' ';
        T[i].ps_fs = nil;
        T[i].ps_nb = nil;
        T[i].ps_pr = nil;
    }
    
    /* Create sample tree as shown in the example */
    /* Root node */
    T[1].info = 'A';
    T[1].ps_fs = 2;
    T[1].ps_nb = nil;
    T[1].ps_pr = nil;
    
    /* Level 1 nodes */
    T[2].info = 'B';
    T[2].ps_fs = 4;
    T[2].ps_nb = 3;
    T[2].ps_pr = 1;
    
    T[3].info = 'C';
    T[3].ps_fs = 6;
    T[3].ps_nb = nil;
    T[3].ps_pr = 1;
    
    /* Level 2 nodes */
    T[4].info = 'D';
    T[4].ps_fs = nil;
    T[4].ps_nb = 5;
    T[4].ps_pr = 2;
    
    T[5].info = 'E';
    T[5].ps_fs = nil;
    T[5].ps_nb = nil;
    T[5].ps_pr = 2;
    
    T[6].info = 'F';
    T[6].ps_fs = nil;
    T[6].ps_nb = 7;
    T[6].ps_pr = 3;
    
    T[7].info = 'G';
    T[7].ps_fs = nil;
    T[7].ps_nb = 8;
    T[7].ps_pr = 3;
    
    T[8].info = 'H';
    T[8].ps_fs = nil;
    T[8].ps_nb = nil;
    T[8].ps_pr = 3;
}

void menu() {
    printf("\n==== MENU NON BINARY TREE ====\n");
    printf("1. Create Tree\n");
    printf("2. Check if Tree is Empty\n");
    printf("3. Traversal PreOrder\n");
    printf("4. Traversal InOrder\n");
    printf("5. Traversal PostOrder\n");
    printf("6. Traversal Level Order\n");
    printf("7. Search\n");
    printf("8. Count Elements\n");
    printf("9. Count Leaves\n");
    printf("10. Find Level of Element\n");
    printf("11. Find Depth of Tree\n");
    printf("12. Print Tree\n");
    printf("13. Create Sample Tree\n");
    printf("14. Display Tree Structure\n");
    printf("0. Exit\n");
    printf("Choose: ");
}

int main() {
    Isi_Tree tree;
    int choice, num_nodes, max_nodes = 0;
    infotype element;
    int level;
    
    /* Initialize tree */
    for (int i = 0; i <= jml_maks; i++) {
        tree[i].info = ' ';
        tree[i].ps_fs = nil;
        tree[i].ps_nb = nil;
        tree[i].ps_pr = nil;
    }
    
    do {
        menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\n=== CREATE TREE ===\n");
                printf("Enter number of nodes: ");
                scanf("%d", &num_nodes);
                
                if (num_nodes > jml_maks) {
                    printf("Error: Maximum number of nodes is %d\n", jml_maks);
                } else {
                    Create_tree(tree, num_nodes);
                    max_nodes = num_nodes;
                    printf("Tree created successfully!\n");
                }
                break;
                
            case 2:
                printf("\n=== CHECK IF TREE IS EMPTY ===\n");
                if (IsEmpty(tree)) {
                    printf("Tree is empty!\n");
                } else {
                    printf("Tree is not empty!\n");
                }
                break;
                
            case 3:
                printf("\n=== TRAVERSAL PREORDER ===\n");
                PreOrder(tree);
                break;
                
            case 4:
                printf("\n=== TRAVERSAL INORDER ===\n");
                InOrder(tree);
                break;
                
            case 5:
                printf("\n=== TRAVERSAL POSTORDER ===\n");
                PostOrder(tree);
                break;
                
            case 6:
                printf("\n=== TRAVERSAL LEVEL ORDER ===\n");
                Level_order(tree, max_nodes);
                break;
                
            case 7:
                printf("\n=== SEARCH ===\n");
                printf("Enter element to search: ");
                scanf(" %c", &element);
                
                if (Search(tree, element)) {
                    printf("Element '%c' found in the tree!\n", element);
                } else {
                    printf("Element '%c' not found in the tree!\n", element);
                }
                break;
                
            case 8:
                printf("\n=== COUNT ELEMENTS ===\n");
                printf("Number of elements in tree: %d\n", nbElmt(tree));
                break;
                
            case 9:
                printf("\n=== COUNT LEAVES ===\n");
                printf("Number of leaves in tree: %d\n", nbDaun(tree));
                break;
                
            case 10:
                printf("\n=== FIND LEVEL OF ELEMENT ===\n");
                printf("Enter element to find level: ");
                scanf(" %c", &element);
                
                level = Level(tree, element);
                if (level != -1) {
                    printf("Level of element '%c': %d\n", element, level);
                } else {
                    printf("Element '%c' not found in the tree!\n", element);
                }
                break;
                
            case 11:
                printf("\n=== FIND DEPTH OF TREE ===\n");
                printf("Depth of tree: %d\n", Depth(tree));
                break;
                
            case 12:
                printf("\n=== PRINT TREE ===\n");
                PrintTree(tree);
                break;
                
            case 13:
                printf("\n=== CREATE SAMPLE TREE ===\n");
                create_sample_tree(tree);
                max_nodes = 8;
                printf("Sample tree created successfully!\n");
                break;
                
            case 14:
                printf("\n=== DISPLAY TREE STRUCTURE ===\n");
                display_tree(tree);
                break;
                
            case 0:
                printf("\nExiting program. Goodbye!\n");
                break;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}