angular.module("app.directives", []).directive "formHgroup", ->
    template: '''
    <div class="form-group" ng-class="{ 'has-error': has_error }">
        <label class="col-sm-4 control-label" for="{{for}}"><span tooltip="{{labelPopover}}">{{label}}</span></label>
        <div class="input-group col-sm-8 col-md-7">
            <span ng-transclude></span>
            <span ng-if="addon" class="input-group-addon">{{addon}}</span>
        </div>
        <div class="col-sm-offset-4" ng-show="error_message"><span class="help-block text-danger">{{error_message | translate}}</span></div>
        <div class="col-sm-offset-4" ng-show="help" ng-if="helpIf"><span class="help-block">{{help}}</span></div>
    </div>
    '''
    replace: true
    transclude: true
    require: "^form"
    scope:
        label: "@"
        addon: "@"
        help: "@"
        helpIf: "@"
        labelPopover: "@"

    link: (scope, element, attrs, formController) ->
        formName = formController.$name
        fieldName = element.find("[name]").attr("name")
        field = scope.$parent[formName][fieldName]
        return unless field
        field.clear_errors = ->
            scope.has_error = false
            scope.error_message = field.$error.message = ''
        id = "fgh_#{formName}_#{fieldName}"
        element.find(":input").attr("id", id)
        scope.for = id
        watchExpression = "#{formName}.#{fieldName}.$viewValue"
        scope.$parent.$watch watchExpression, (value) ->
            scope.has_error = !field.$valid and !field.$pristine
        errorExpression = "#{formName}.#{fieldName}.$error.message"
        scope.$parent.$watch errorExpression, (error_message) ->
            scope.error_message = error_message
            scope.has_error = scope.has_error or !!error_message

    controller: ($scope, $element) ->
        @clear_errors = ->
            $scope.error_message = null
            $scope.has_error = false
        return @



angular.module("app.directives").directive "formHgroupSubmitBtn", ->
    template: '''
    <div class="form-group hgroup-button">
        <div class="col-sm-offset-4 col-sm-3 no-lr-padding">
            <button type="submit" class="btn btn-primary"><span ng-transclude></span></button>
        </div>
        <div class="col-sm-4"><span class="help-block">{{help}}</span></div>
    </div>
    '''
    replace: true
    transclude: true
    require: "^form"
    scope:
        help: "@"

    link: (scope, element, attrs, formController) ->
        watchExpression = formController.$name + ".$valid"
        scope.$parent.$watch watchExpression, (valid) ->
            element.find("button").attr("disabled", !valid)
            help = element.find(".help-block")
            if valid then help.show() else help.hide()



angular.module("app.directives").directive "formHgroupError", ->
    template: '''
    <div class="form-group" ng-show="error_message">
        <div class="col-sm-12">
            <div class="form-error alert alert-danger">
                <i class="fa fa-exclamation"></i> &nbsp; &nbsp;
                {{error_message | translate}}
            </div>
        </div>
    </div>
    '''
    replace: true
    transclude: true
    require: "^form"

    link: (scope, element, attrs, formController) ->
        watchExpression = formController.$name + ".$error.message"
        scope.$watch watchExpression, (value) ->
            scope.error_message = value



angular.module("app.directives").directive "formHgroupValue", ->
    template: '''
    <div class="form-group">
        <label class="col-sm-4 control-label">{{label}}</label>
        <div class="col-sm-8 col-md-6 balance-label"><span class="cell" ng-show="showValue"><span ng-transclude></span> {{symbol}}</span></div>
    </div>
    '''
    replace: true
    transclude: true
    scope:
        symbol: "@"
        label: "@"
        showValue: "@"
    compile: (element, attrs) ->
        attrs.showValue = true if attrs.showValue == undefined



angular.module("app.directives").directive "formHgroupNote", ->
    template: '''
    <div class="form-group hgroup-no-top-space">
       <div class="col-sm-offset-4"><span class="help-block"><span ng-transclude></span></span></div>
    </div>
    '''
    replace: true
    transclude: true
    scope: false
