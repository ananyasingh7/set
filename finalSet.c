/*
Ananya Singh 
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20;

struct Node {
	int element;
	struct Node *next;
};

struct Set {
    struct Node *head;
    struct Node *tail;
};


struct Set SET_new() {
    struct Set set;
    set.head = NULL;
    return set;
}

int SET_contains(struct Set *set, int element) {
    struct Node *p;
    for(p = set->head; p != NULL; p = p->next){
        if(p->element == element){
            return 1;
        }
    }

    return 0;
}

void SET_add(struct Set *set, int element) {
    if(SET_contains(set,element)){
        printf("Element already in set\n");
    }else{
        struct Node *node = malloc(sizeof(struct Node));
        node->element = element;
	    node->next = set->head;
        if(set->head == NULL){
            set->tail = node;
        }
        
        set->head = node;
    }

}

void SET_remove(struct Set *set, int element) {
    struct Node *before;
    struct Node *current;
    struct Node *temp;

    for(current = set->head; current != NULL; current = current->next){
        if(current->element == element){
            if(set->head == current){
                temp = current->next;
                set->head =  temp;                
            }
        
            else if(element == current->element){
                temp = current->next;
                before->next = temp; 
            }

            else if(set->tail->element == element){
                before->next = NULL;
                set->tail = before;
            }          
            free(current);
        }
        before = current;
    }

    for(current = set->head; current !=NULL; current = current->next){
        if(current->next == NULL){
            set->tail = current;
        }
    }


}


/*
Union of two sets. The union of two sets A and B is the set of elements which are in A, in B, or in both A and B.  
For example, if A = {1, 3, 5, 7} and B = {1, 2, 4, 6} then A ∪ B = {1, 2, 3, 4, 5, 6, 7}.
*/


struct Set SET_union(struct Set s, struct Set t) { 
    struct Node *p;
    struct Set temp;
    struct Set empty = SET_new();
    temp.head = s.head;  /*seg fault fix if you don't include this */
    temp.tail = s.tail; /*seg fault fix if you don't include this */
    temp.tail->next = NULL; /*seg fault fix if you don't include this */

    for(p = s.head; p != NULL; p= p->next){
        if(SET_contains(&temp,p->element) == 0){ /*cant contain */
            SET_add(&temp, p->element);
        }
    }

    for(p = t.head; p != NULL; p = p->next){
        if(SET_contains(&temp,p->element) == 0){ /*cant contain */
            SET_add(&temp, p->element);
        }
    }

    if(temp.head == NULL){
        return empty;
    }

    return temp;
    
}



struct Set SET_intersection(struct Set s, struct Set t) {
    struct Node *p;
    struct Set temp = SET_new();
    struct Set empty = SET_new();

    for(p = s.head; p != NULL; p = p->next){
        if(SET_contains(&s,p->element)){
            if(SET_contains(&t,p->element)){
                SET_add(&temp,p->element);
            }
        }
    }

    if(temp.head == NULL){
        return empty;
    }
    
    return temp;

}




struct Set SET_difference(struct Set s, struct Set t) {
	/* return s - t */
    struct Node *p;
    struct Set empty = SET_new();
    struct Set temp = SET_new();
    for(p=s.head;p!=NULL;p=p->next){
        if(SET_contains(&s,p->element)){
            if(SET_contains(&t,p->element) == 0){
                SET_add(&temp, p->element);
            }
        }
    }

    if(temp.head == NULL){
        return empty;
    }

    return temp;
   
}




int SET_min(struct Set *set) {
    int min = set->head->element;
    struct Node *p;
    for(p = set->head; p != NULL; p = p->next){
        if(p->element<min){
            min = p->element;
        }
    }

    return min;
}

int SET_max(struct Set *set) {
    int max = set->head->element;
    struct Node *p;
    for(p = set->head; p != NULL; p = p->next){
        if(p->element > max){
            max = p->element;
        }
    }
    
    return max;
}

int SET_cardinality(struct Set *set) {
    struct Node *p;
	int n = 0;
	for (p = set->head; p != NULL; p= p->next) {
		++n;
	}
	return n;
}





int main() {
    struct Set set = SET_new();
    struct Set setBeta = SET_new();

    struct Node *p;
    SET_add(&set, 203);
    SET_add(&set, -293);
    SET_add(&set, 3);
    SET_add(&set, 40);
    SET_add(&set, 100000);
    SET_add(&set, -102334);
    SET_add(&set, 7);
    SET_add(&set, 11);
    SET_add(&set, 690);
    SET_add(&set, 420);
    SET_add(&set, 0);
    
    SET_add(&setBeta, -293);
    SET_add(&setBeta, 7);
    SET_add(&setBeta, 344);
    SET_add(&setBeta, 23);
    SET_add(&setBeta, 11);
    SET_add(&setBeta, 1);
    SET_add(&setBeta, 2);
    SET_add(&setBeta, 4);
    SET_add(&setBeta, 6);
    SET_add(&setBeta, 8);
    SET_add(&setBeta, -25);
    /**
    struct Set intersection = SET_intersection(set, setBeta);

    
    int a = SET_cardinality(&intersection);
    printf("Head: %d   Tail: %d Length: %d\n", intersection.head->element, intersection.tail->element, a);
    for(p = setBeta.head; p != NULL; p = p->next){
        printf("Element:%d\n",p->element);
    }

    printf("Test Run 1\n\n\n");
    **/
    int max1 = SET_max(&set);
    int min1 = SET_min(&set);
    int a = SET_cardinality(&set);
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n\n");
    printf("Head: %d   Tail: %d Cardinality: %d\n", set.head->element, set.tail->element, a);
    printf("Max:%d     Min: %d\n",max1,min1);
    printf("--------------------------------------------------------------------------------------\n\n\n");


    SET_remove(&set, 100000);
    printf("AFTER REMOVING AN ELEMENT IN THE MIDDLE: 100000\n");
    int max2 = SET_max(&set);
    int min2 = SET_min(&set);
    int b = SET_cardinality(&set);
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n\n");
    printf("Head: %d   Tail: %d Cardinality: %d\n", set.head->element, set.tail->element, b);
    printf("Max:%d     Min: %d\n",max2,min2);
    printf("--------------------------------------------------------------------------------------\n\n\n");

    
    SET_remove(&set, 0);
    SET_remove(&set, 420);
    SET_remove(&set, 203);
    SET_remove(&set, -293);
    
    printf("AFTER REMOVING HEAD : 0\n");
    printf("AFTER REMOVING HEAD2: 420\n");
    printf("AFTER REMOVING TAIL: 203\n");
    printf("AFTER REMOVING TAIL2: -293\n");
    int max3 = SET_max(&set);
    int min3 = SET_min(&set);
    int c = SET_cardinality(&set);
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n\n");
    printf("Head: %d   Tail: %d Cardinality: %d\n", set.head->element, set.tail->element, c);
    printf("Max:%d     Min: %d\n",max3,min3);
    printf("--------------------------------------------------------------------------------------\n\n\n");
    
    printf("ADDING DUPLICATE: 7\n");
    printf("ADDING DUPLICATE: 40\n");
    SET_add(&set, 7);
    SET_add(&set, 40);
    int max4 = SET_max(&set);
    int min4 = SET_min(&set);
    int e = SET_cardinality(&set);
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n\n");
    printf("Head: %d   Tail: %d Cardinality: %d\n", set.head->element, set.tail->element, e);
    printf("Max:%d     Min: %d\n",max4,min4);
    printf("--------------------------------------------------------------------------------------\n\n\n");

    
    struct Set inter = SET_intersection(set,setBeta);
    printf("INTERSECTION\n\n");
    printf("SET 1: ");
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");


    printf("SET 2: ");
    printf("{");
    for(p = setBeta.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");


    printf("Intersection: "); 
    printf("{");
    for(p = inter.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");

    

    
    
    printf("--------------------------------------------------------------------------------------\n\n\n");

    struct Set unionSet = SET_union(set,setBeta);
    printf("UNION\n\n");
    printf("SET 1: ");
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");


    printf("SET 2: ");
    printf("{");
    for(p = setBeta.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");


    printf("Union: ");
    printf("{");
    for(p = unionSet.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");

    

    
    
    printf("--------------------------------------------------------------------------------------\n\n\n");

    struct Set differ = SET_difference(set,setBeta);
    printf("DIFFERENCE\n\n");
    printf("SET 1: ");
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");


    printf("SET 2: ");
    printf("{");
    for(p = setBeta.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");


    printf("Difference:");
    printf("{");
    for(p = differ.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");

    

    
    
    printf("--------------------------------------------------------------------------------------\n\n\n");

    SET_remove(&setBeta, -293);
    SET_remove(&setBeta, 7);
    SET_remove(&setBeta, 344);
    SET_remove(&setBeta, 23);
    SET_remove(&setBeta, 11);
    SET_remove(&setBeta, 1);
    SET_remove(&setBeta, 2);
    SET_remove(&setBeta, 4);
    SET_remove(&setBeta, 6);
    SET_remove(&setBeta, 8);
    SET_remove(&setBeta, -25);
    
    
    struct Set differ1 = SET_difference(set,setBeta);
    /*struct Set unionSet1 = SET_union(set,setBeta);*/
    struct Set inter1 = SET_intersection(set,setBeta);
    printf("EMPTIED SET2\n\n");
    printf("SET 1: ");
    printf("{");
    for(p = set.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");



    printf("SET 2: ");
    printf("{");
    for(p = setBeta.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");


    printf("Difference:");
    printf("{");
    for(p = differ1.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");

    printf("Union:");
    printf("{");
    printf("}\n");

    printf("Intersection:");
    printf("{");
    for(p = inter1.head; p != NULL; p = p->next){
        printf("%d, ",p->element);
    }
    printf("}\n");

    

    
    
    printf("--------------------------------------------------------------------------------------\n\n\n");







    return 0;


}