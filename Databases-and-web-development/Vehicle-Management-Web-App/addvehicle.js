import { createClient } from 'https://cdn.jsdelivr.net/npm/@supabase/supabase-js/+esm';

const supabase =createClient('https://jcznlxcuocnxwaisnigv.supabase.co','eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Impjem5seGN1b2NueHdhaXNuaWd2Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDQ5MDk2NDQsImV4cCI6MjA2MDQ4NTY0NH0.fJtugtc0ZY1RyeD35NboZiYMVp4aoJxCbkRIN008Syc');

let rego = '', make = '', model = '', colour = '';
let name = '', address = '', dob = '', license = '', expire = '';

//get elements from the DOM by ID that are going to be accessed
const pform=document.querySelector('#pform');
const messageVehicle=document.querySelector('#message-vehicle');
const messageOwner=document.querySelector('#message-owner');
const resultsDiv=document.querySelector('#owner-results');
const ownerInput=document.querySelector('#owner');
const checkButton=document.querySelector('#check');
const addForm=document.querySelector('#addform');
const addOwner=document.querySelector('#add');
const addVehicle=document.querySelector('#add-vehicle');
const newOwner=document.querySelector('#new-owner');
const addVehicleForm=document.querySelector('#addvehicle');

//hide button initially
//checkButton.style.display = 'none';
addForm.style.display ='none';
addVehicle.style.display='none';

ownerInput.addEventListener('input', () => {
  if (ownerInput.value.trim() !== '') {//is owner field null?
    checkButton.disabled =false;
  } else {
    checkButton.disabled =true;
  }
});
//event listener detects when submit clicked and runs fuction
pform.addEventListener('submit', async(event) =>{
  event.preventDefault();//do not refresh page (default of submit)

  //get values from input boxes
  const rego =document.querySelector('#rego').value.trim();
  const make =document.querySelector('#make').value.trim();
  const model =document.querySelector('#model').value.trim();
  const colour =document.querySelector('#colour').value.trim();
  const owner =document.querySelector('#owner').value.trim();

  resultsDiv.innerHTML ='';//clear any prev results
  addForm.style.display ='none';
  //create query on People table
  let query = supabase.from('People').select();//all columns

  
 //(owner && colour && model && make && rego)
  if (owner && colour && model && make && rego){
    query = query.ilike('Name',`%${owner}%`);
  }
  else{//either both NULL or both fields filled in
    messageVehicle.textContent ='Error'
    return;
  }


  //run query
  const {data,error} = await query;//'data' contains matching rows, error comtains any error

  //if error returned
  if (error){
    messageVehicle.textContent ='Error'
    return;
  }

  //no matching owner
  if (data.length === 0){
    newOwner.disabled = false;
    addForm.style.display ='flex';
    //messageVehicle.textContent='Add new owner';
    
  }
  else{
    messageVehicle.textContent ='Search successful';

    //loop through results
    for (const row of data) {
      //create a button for the current row
      const rowDiv = document.createElement('div');
      rowDiv.classList.add('row'); //add to button class for styling
      /*rowDiv.innerHTML = `
        <div>personid: ${row.PersonID}</div>
        <div>name: ${row.Name}</div>
        <div>address: ${row.Address}</div>
        <div>dob: ${row.DOB}</div>
        <div>licensenumber: ${row.LicenseNumber}</div>
        <div>expirydate: ${row.ExpiryDate}</div>
      `;*/
      rowDiv.textContent = `
        personid: ${row.PersonID}
        name: ${row.Name}
        address: ${row.Address}
        dob: ${row.DOB}
        licensenumber: ${row.LicenseNumber}
        expirydate: ${row.ExpiryDate}
      `;
      
      const selectButton=document.createElement('button');
      selectButton.textContent ="Select owner";
      selectButton.classList.add('select-button');
  
      //add event listener to button
      selectButton.addEventListener('click', async () =>{
          if(!(owner && colour && model && make && rego)){
              messageVehicle.textContent= 'Error';
              return;
          }
          const { error } = await supabase
          .from('Vehicles')
          .insert({ VehicleID: rego, Make: make, Model: model, Colour: colour, OwnerID: row.PersonID, });
  
          if (error) {
            //console.log('Insert Owner Error:', error);
            messageVehicle.textContent= 'Error';
            return;
          } else {
              messageVehicle.textContent='Vehicle added successfully';
          }
        
      });
    
      //add button to the results container
      rowDiv.appendChild(selectButton);
      resultsDiv.appendChild(rowDiv);
    }
  
   /*newOwner.classList.add('none-match-button');
   newOwner.textContent ='New owner';*/
   newOwner.disabled = false;
   newOwner.addEventListener('click', () =>{
      addForm.style.display ='flex';
      messageOwner.textContent='Add new owner';
   });
  
   resultsDiv.appendChild(newOwner);
  }


  
  
});

//form for adding a new owner
addForm.addEventListener('submit', async (event) => {
    event.preventDefault();
    //people
    name = document.querySelector('#name').value.trim();
    address = document.querySelector('#address').value.trim();
    dob = document.querySelector('#dob').value.trim();
    license = document.querySelector('#license').value.trim();
    expire = document.querySelector('#expire').value.trim();
    //vehcile
    rego = document.querySelector('#rego').value.trim();
    make = document.querySelector('#make').value.trim();
    model = document.querySelector('#model').value.trim();
    colour = document.querySelector('#colour').value.trim();

    const messageVehicle = document.querySelector('#message-vehicle');
    const messageOwner =document.querySelector('#message-owner');
    //check for missing owner fields
    if (!(name && address && dob && license && expire)) {
      messageOwner.textContent = 'Error';
      return;
    }
  
    //check for exact match
    const { data: existing, error: searchError } = await supabase
      .from('People')
      .select()
      .eq('Name', name)
      .eq('Address', address)
      .eq('DOB', dob)
      .eq('LicenseNumber', license)
      .eq('ExpiryDate', expire);
  
    if (searchError) {
      messageOwner.textContent = 'Error';
      return;
    }
  
    if (existing.length > 0) {
      messageOwner.textContent = 'Error';
      return;
    }
  
    const { error: insertOwnerError } = await supabase
      .from('People')
      .insert({
        Name: name,
        Address: address,
        DOB: dob,
        LicenseNumber: license,
        ExpiryDate: expire
      });
  
    if (insertOwnerError) {
      //console.log('Insert Owner Error:', insertOwnerError);
      messageOwner.textContent = 'Error';
      return;
    }
    else{
      messageOwner.textContent = 'Owner added successfully';
      addVehicle.style.display='flex';
      checkButton.disabled = true;
    }
    addVehicle.style.display='flex';
    messageOwner.textContent = 'Owner added successfully';
    
  });

  addVehicleForm.addEventListener('submit', async (event) => {
    event.preventDefault();
    //get new owners ID
    const { data: newOwnerData, error: fetchOwnerError } = await supabase
    .from('People')
    .select('PersonID')
    .eq('Name', name)
    .eq('Address', address)
    .eq('DOB', dob)
    .eq('LicenseNumber', license)
    .eq('ExpiryDate', expire)

  if (fetchOwnerError || !newOwnerData) {
    messageOwner.textContent = 'Error duplicate';
    return;
  }

  const newOwnerId = newOwnerData[0]?.PersonID;

  //make sure feilds not empty
  if (!(rego && make && model && colour)) {
    messageVehicle.textContent = 'Error fields empty';
    return;
  }
  
  //insert new vehicle
  const { error: insertVehicleError } = await supabase
    .from('Vehicles')
    .insert({
      VehicleID: rego,
      Make: make,
      Model: model,
      Colour: colour,
      OwnerID: newOwnerId
    });

  if (insertVehicleError) {
    messageVehicle.textContent = 'Error adding vehicle';
    return;
  } else {
    messageVehicle.textContent = 'Vehicle added successfully';
    addForm.style.display = 'none';//hide forms
    addVehicle.style.display='none';
  }
  messageVehicle.textContent = 'Vehicle added successfully';

  });
  

