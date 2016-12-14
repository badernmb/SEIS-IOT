
// getting first empty row in column
function getFirstEmptyRow() {
  var spr = SpreadsheetApp.getActiveSpreadsheet();
  var column = spr.getRange('C:C');
  var values = column.getValues(); // get all data in one call
  var ct = 0;
  while ( values[ct][0] != "" ) {
    ct++;
  }
  return (ct);
}

// this function gets the last level of water then copy it to another column
// not uesed anymore
function progress()
{ 

  var sheet = SpreadsheetApp.getActiveSheet();
  
  var distanceCell = sheet.getRange(2,1);  
  var distanceValue=distanceCell.getValue();
  
  var topCell = sheet.getRange(2,2);  
  var topValue=topCell.getValue();
  
  var oldCell=sheet.getRange(getFirstEmptyRow(),3);
  var oldDistacne=oldCell.getValue();
  
  if(topValue =="Closed" && oldDistacne !=distanceValue)
  {
  var cell = sheet.getRange(getFirstEmptyRow()+1,3);
   cell.setValue(distanceValue);
    target();
  }
  
  }

// this function caluclates how far you are from target.
// not used anymore
function target(){
 
  var sheet = SpreadsheetApp.getActiveSheet();
  
  var distanceCell = sheet.getRange(getFirstEmptyRow(),3);  
  var distanceValue=distanceCell.getValue();
 
  var oldCell=sheet.getRange(getFirstEmptyRow()-1,3);
  var oldDistacne=oldCell.getValue();
  
  var cell = sheet.getRange(2,4);
  var oldTargetValue=cell.getValue();
  
  var cell1 = sheet.getRange(2,5);
  var oldCell1=cell1.getValue();
  
  
  if ((distanceValue<oldDistacne) && (distanceValue !=oldCell1))
  {
  var newTarget=oldTargetValue + (oldDistacne - distanceValue);
    cell1.setValue(distanceValue);
    cell.setValue(newTarget);
    
  }
}
 
// this function runs at mid night to set the progressinto 0 and runs updateDailyTarget()function

  function Clean(){
    
  var sheet = SpreadsheetApp.getActiveSheet();
  var column = sheet.getRange('C:C');
  var values = column.getValues(); // get all data in one call
  var ct = 1;
    
    updateDailyTarget();
    
  var progress = sheet.getRange(2,3);  
    progress.setValue(0)
    

  
  }

// this function updates the chart history 
function updateDailyTarget(){
 
   var sheet = SpreadsheetApp.getActiveSheet();
   var column = sheet.getRange('G:G');
   var values = column.getValues();
   var ct = 0;
  
  var d=new Date();
  
    while ( values[ct][0] != "" ) {
    ct++;
} 
  
   var Cell=sheet.getRange(ct + 1,7);
   Cell.setValue(d);
  
   var target = sheet.getRange(2,3);
   var oldTargetValue=target.getValue();
  
 var targetForHistory=sheet.getRange(ct + 1, 8)
 targetForHistory.setValue(oldTargetValue);
  
}


