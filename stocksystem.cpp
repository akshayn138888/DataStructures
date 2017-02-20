//
//  stocksystem.cpp
//  assignment 4
//
//  Created by Akshay Nanda on 2016-03-15.
//  Copyright © 2016 Akshay Nanda. All rights reserved.

#include "stocksystem.h"

StockSystem::StockSystem()
{
    balance = 100000;
}

double StockSystem::GetBalance()
{
    return balance;
}
bool StockSystem::StockNewItem(StockItem item)
{
    if (records.Search(item)==false)
    {
        records.Insert(item);
        return true;
    }
    else
    {
        return false;
    }
    
}
bool StockSystem::EditStockItemDescription( int itemsku, string desc)
{
    if (records.Size() == 0)
    {
        return false;
    }
    else
    { Node<StockItem>* nodeofref1 = records.GetRoot();
  
        int j = records.Height();
        int k = 1;
        bool itemfound = false;
    
        while(nodeofref1->data.GetSKU() != itemsku && k <= j)
        {
            if (itemsku > nodeofref1->data.GetSKU() && nodeofref1->right != NULL)
            {
                nodeofref1 = nodeofref1->right;
            }
            else if (itemsku < nodeofref1->data.GetSKU() && nodeofref1-> left != NULL)
            {
                nodeofref1 = nodeofref1-> left;
            }
            k++;
        }
        if (k <= j)
        {
            itemfound = true;
        }
        
        else
        {
            itemfound = false;
        }
        if (itemfound)
        {
            nodeofref1->data.SetDescription(desc);
            return true;
        }
        else
        {
            return false;
        }
    }
}
bool StockSystem::EditStockItemPrice(int itemsku, double retailprice)
{
    if (records.Size() == 0)
    {
        return false;
    }
    else
    {Node<StockItem>* nodeofref= records.GetRoot();
      
        int j = records.Height();
        int k = 1;
        bool itemfound = false;

        while(nodeofref->data.GetSKU() != itemsku&&k <= j)
        {
            if (itemsku > nodeofref->data.GetSKU() && nodeofref->right != NULL)
            {
                nodeofref = nodeofref->right;
            }
            else if (itemsku < nodeofref->data.GetSKU() && nodeofref-> left != NULL)
            {
                nodeofref = nodeofref-> left;
            }
            k++;
        }
        if (k <= j)
        {
            itemfound = true;
        }
        else
        {
            itemfound = false;
        }
        
        if (itemfound)
        {
            nodeofref->data.SetPrice(retailprice);
            return true;
        }
        else
        {
            return false;
        }
    }
}
bool StockSystem::Restock(int itemsku, int quantity, double unitprice)
{
    
    if (balance < quantity * unitprice)
    {
        return false;
    }
    else if (records.Size() == 0)
    {
        return false;
    }
    else
    {
        Node<StockItem>* nodeofref= records.GetRoot();
        bool itemfound = false;
        int j = records.Height();
        int k = 1;
        while(nodeofref->data.GetSKU() != itemsku && k <= j)
        {
            if (itemsku > nodeofref->data.GetSKU() && nodeofref->right != NULL)
            {
                nodeofref = nodeofref->right;
            }
            else if (itemsku < nodeofref->data.GetSKU() && nodeofref-> left != NULL)
            {
                nodeofref = nodeofref-> left;
            }
            k++;
        }
        if (k <= j)
        {
            itemfound = true;
        }
        else
        {
            itemfound = false;
        }
        if (itemfound)
        {
            nodeofref->data.SetStock(quantity + nodeofref->data.GetStock());
            balance = balance - quantity*unitprice;
            return true;
        }
        else
        {
            return false;
        }
    }
}
bool StockSystem::Sell(int itemsku,int quantity)
{
    if ( records.Size()==0)
    {
        return false;
    }
    else
    {
        Node<StockItem>* nodeofref= records.GetRoot();
        bool itemfound = false;
        int j = records.Height();
        int k = 1;
        while(nodeofref->data.GetSKU() != itemsku && k <= j)
        {
            if (itemsku > nodeofref->data.GetSKU() && nodeofref->right != NULL)
            {nodeofref = nodeofref->right;
            }
            else if (itemsku < nodeofref->data.GetSKU() && nodeofref-> left != NULL)
            {nodeofref = nodeofref-> left;
            }
            k++;
        }
        if (k <= j)
        {itemfound = true;
        }
        else
        {
            itemfound = false;
        }
        if (itemfound==true)
        {if (nodeofref->data.GetStock() == 0)
            {return false;
            }
            else if (nodeofref->data.GetStock() >= quantity)
            {
                nodeofref->data.SetStock(nodeofref->data.GetStock() - quantity);
                balance = balance + quantity * nodeofref->data.GetPrice();
                return true;
            }
            else
            
            {
                balance = balance + nodeofref->data.GetPrice() * nodeofref->data.GetStock();
             nodeofref->data.SetStock(0);
                return true;
            }
        }
        else
        {
            return false;
        }
        
    }
}