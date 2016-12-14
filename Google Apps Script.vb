

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

  function Clean(){
    
  var sheet = SpreadsheetApp.getActiveSheet();
  var column = sheet.getRange('C:C');
  var values = column.getValues(); // get all data in one call
  var ct = 1;
    
    updateDailyTarget();
    
  var target = sheet.getRange(2,4);  
    target.setValue(0)
    
    var lastSteep = sheet.getRange(2,5);  
    lastSteep.setValue("");
 
  while ( values[ct][0] != "" ) {
    
    var oldCell=sheet.getRange(ct + 1,3);
     oldCell.setValue("");
    
    ct++;
} 
  
  }


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
  
   var target = sheet.getRange(2,4);
   var oldTargetValue=target.getValue();
  
 var targetForHistory=sheet.getRange(ct + 1, 8)
 targetForHistory.setValue(oldTargetValue);
  
}