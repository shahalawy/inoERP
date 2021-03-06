<?php

/**
 * inoERP
 *
 * @copyright   2014 Nishit R. Das
 * @license     https://www.mozilla.org/MPL/2.0/
 * @link        http://inoideas.org
 * @source code https://github.com/inoerp/inoERP
 */

/**
 * coa
 * coa is used for mapping different  business segments that needs financial account mapping
 * Contains all the gl_calendar information, such as - name, description , balancing, natural_account, etc
 * 
 */
class coa extends dbObject {

 public static $table_name = "coa";
 public static $primary_column = "coa_id";
 public static $key_column = "coa_structure_id"; //same as option_header_id
 public static $module = "gl";
 public static $system_info = [
  'name' => 'COA',
  'number' => '1103',
  'description' => 'Chart Of Account',
  'version' => '0.1.1',
  'db_version' => '1001',
  'mod_version' => '1.1.1',
  'dependent_class' => array('coa_segment_values'),
  'primary_entity_cb' => '',
  'module_name' => 'gl',
  'weight' => 3
 ];
 public $field_a = ['coa_id',
  'coa_structure_id',
  'coa_name',
  'description',
  'balancing',
  'cost_center',
  'natural_account',
  'inter_company',
  'field1',
  'field2',
  'field3',
  'field4',
  'field5',
  'field6',
  'field7',
  'field8',
  'status',
  'rev_enabled_cb',
  'rev_number',
  'created_by',
  'creation_date',
  'last_update_by',
  'last_update_date',
 ];
 public $initial_search = [
  'coa_structure_id',
  'description',
  'coa_sequence'
 ];
 public $fields_inForm_notInDataBase = [
 ];
 public $fields_inHeader_needsToBeInserted_inPOST = [
 ];
 public $checkbox = [
  'rev_enabled_cb',
 ];

 public $requiredField = [
  'coa_structure_id',
  'description',
  'balancing',
  'cost_center',
  'natural_account',
  'inter_company'
 ];
// public $dateFields;
//varibles required for search
 public $search = [
  '_show_update_path' => 1,
  '_show_view_path' => 1,
 ];
 public $pageTitle = " Chart Of Account "; //page Title
 public $coa_id;
 public $coa_structure_id;
 public $coa_name;
 public $description;
 public $balancing;
 public $cost_center;
 public $natural_account;
 public $inter_company;
 public $field1;
 public $field2;
 public $field3;
 public $field4;
 public $field5;
 public $field6;
 public $field7;
 public $field8;
 public $coa_sequence_value;
 public $coa_sequence_field;
 public $ef_id;
 public $status;
 public $rev_enabled_cb;
 public $rev_number;
 public $created_by;
 public $creation_date;
 public $last_update_by;
 public $last_update_date;

public function _before_save(){
 if(empty($this->coa_sequence)){
  
 }
}

 Public static function coa_account_types() {
  $option_header = option_header::find_by_name('COA_ACCOUNT_TYPE');
  $ol = new option_line();
  $coa_account_types = $ol->findBy_parentId($option_header->option_header_id);
  return $coa_account_types;
 }

 Public static function find_by_structure($coa_structure_id = '') {
  global $db;
  $sql = " SELECT * FROM  " . self::$table_name;
  $sql .= " WHERE coa_structure_id = '{$coa_structure_id}' ";
  $result = $db->find_by_sql($sql);
  return !empty($result) ? array_shift($result) : false;
 }

 Public function findBy_structureId() {
  global $db;
  $sql = " SELECT * FROM  " . self::$table_name;
  $sql .= " WHERE coa_structure_id = :coa_structure_id ";
  $param_a = ['coa_structure_id'];
  $value_a = [ 'coa_structure_id' => $this->coa_structure_id];
  $result = $db->findBy_sql($sql, $param_a, $value_a);
  return !empty($result) ? array_shift($result) : false;
 }

 Public static function coa_structures() {
  $sql = " SELECT * FROM option_header WHERE option_assignments = 'GL_COA' ";
  $result = self::find_by_sql($sql);
  return $result;
 }

 Public static function coa_display_by_coaId($coaId = '') {
  global $db;
  $sql = " SELECT  field1, field2, field3, field4, field5, 
	 field6, field7, field8 FROM  " . self::$table_name;
  $sql .= " WHERE coa_id = '{$coaId}' ";
  $result = $db->find_by_sql($sql);
  return !empty($result) ? array_shift($result) : false;
 }

 Public static function coa_segments($option_type) {
  $coa_structure_id = option_header::find_by_name($option_type);
  if (!empty($coa_structure_id)) {
   $segments = option_line::find_by_option_id($coa_structure_id->option_header_id);
  }
  return !empty($segments) ? $segments : false;
 }

 Public static function coa_segments_by_optionHeaderId($option_headerId) {
   $segments = option_line::find_by_parent_id($option_headerId);
    return !empty($segments) ? $segments : false;
 }

 public static function find_coa_fields_option($coa_id) {
  $sql = "SELECT balancing, cost_center, 	natural_account, inter_company,
      segment1, segment2, segment3, segment4 FROM "
   . self::$table_name . " where coa_id={$coa_id} LIMIT 1";
  $result_array = self::find_by_sql($sql);
  return !empty($result_array) ? array_shift($result_array) : false;
 }

 public static function find_coa_fields_by_id($coa_id) {
  $sql = "SELECT balancing, cost_center, 	natural_account, inter_company,
      segment1, segment2, segment3, segment4 FROM "
   . self::$table_name . " where coa_id={$coa_id} LIMIT 1";
  $result_array = self::find_by_sql($sql);
  return !empty($result_array) ? array_shift($result_array) : false;
 }

 public static function find_coa_fields_by_id_array($coa_id) {
  global $db;
  $sql = "SELECT balancing, cost_center, 	natural_account, inter_company,
      segment1, segment2, segment3, segment4 FROM "
   . self::$table_name . " where coa_id={$coa_id} LIMIT 1";
  $result_set = $db->query($sql);
  $row = mysql_fetch_row($result_set);
  return $row;
 }

}

$coa = new coa;
//end of coa class
?>
