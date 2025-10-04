import { createClient } from 'https://cdn.jsdelivr.net/npm/@supabase/supabase-js/+esm';

const supabase=createClient('https://jcznlxcuocnxwaisnigv.supabase.co','eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Impjem5seGN1b2NueHdhaXNuaWd2Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDQ5MDk2NDQsImV4cCI6MjA2MDQ4NTY0NH0.fJtugtc0ZY1RyeD35NboZiYMVp4aoJxCbkRIN008Syc');

//get elements from the DOM by ID that are going to be accessed
const form=document.querySelector('#pform');
const messageDiv=document.querySelector('#message');
const resultsDiv=document.querySelector('#results');

//event listener detects when submit clicked and runs fuction
form.addEventListener('submit', async(event)=>{
  event.preventDefault();//do not refresh page (default of submit)

  //get values from input boxes
  const rego=document.querySelector('#rego').value.trim();

  resultsDiv.innerHTML='';//clear any prev results
  
  //create query on Vehicles table
  let query=supabase.from('Vehicles').select();//all columns

  if(rego){//if rego entered, make case insensitive and look for similar
      query=query.ilike('VehicleID',`%${rego}%`);//contains
  }

  else{//either both NULL or both fields filled in
    messageDiv.textContent='Error'
    return;
  }

  let data;
  //run query
  try{
    const result=await query;//'data' contains matching rows, error comtains any error
    if (result.error){
      throw result.error;
    }
    data = result.data;
    if (data.length=== 0){//no matching rows found
      messageDiv.textContent='No result found';
      return;
    }
    
    messageDiv.textContent='Search successful';
  } catch(error){
    messageDiv.textContent='Error'
    return;
  }
  
  //loop through results
  for (const row of data) {
    //create container div for current vehicle
    const rowDiv=document.createElement('div');
    rowDiv.classList.add('row');//add to row class
    rowDiv.textContent=`vehicleID: ${row.VehicleID}|make: ${row.Make}|model: ${row.Model}|colour: ${row.Colour}|ownerID: ${row.OwnerID}|`;
    resultsDiv.appendChild(rowDiv);//add vehicle to overall container, results
  }
  
});
