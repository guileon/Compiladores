//tac_create() ....
//tac_create(int tac_type, HASH_NODE *target, HASH_NODE *op1, HASH_NODE *op2);


TAC * tac_join (TAC * L1, TAC * L2)
{
    TAC * tac;
    if (L1 == NULL)
        return L2;
    if (L2 == NULL)
        return L1;

    for (tac = L2; tac->prev; tac = tac->prev) //soh pra ir pro final da lista mesmo
        ;

    tac->prev = L1;
    return L2;
}

/*void tac_print_singles(TAC *t);
{
	
	if(t->type == TAC_SYMBOL) return;
	
	
	swtich(t->type == TAC_SYMBOL)
	{
		case TACC_ADD:
	}
	
	
	
	
}


???
tac-target = target;
	tac->op1 = op1;
	tac->op2 = op2;
	tac->prev = 0;
	tac->next = 0;
	return tac;
*/

void tac_print_list(TAC *first)
{
	TAC *tac;
	for(tac=first; tac; tac = tac->prev);
		tac_print_single(tac);
}

void tac_join(TAC *l1, TAC *l2)
{
TAC *tac;
if (!l1) return l2;
if (!l2) return l1;

for (tac = l1; tac->prev; tac = tac->prev)
tac->prev = l1
return l2;
}

/*
TAC *tac_reverse(TAC *last)
{
	TAC *first = 0;
	if(last == 0)
		return 0;
	
	for()
		algo
	
	return first;
}
*/
